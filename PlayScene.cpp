#include "PlayScene.h"

#include <random>

#include "GOFactory.h"
#include "Game.h"
#include "CameraComponent.h"
#include "CameraController.h"
#include "RandomMover.h"
#include "ModelRenderComponent.h"
#include "FMODTest.h"
#include "AudioManager.h"

PlayScene::PlayScene() {

	setAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
	setClearFlags(GL_DEPTH_BUFFER_BIT);

	GameObject* obj = GOFactory::instance()->createTeapot();
 	obj->setPosition(glm::vec3(0.0f, 5.0f, 0.0f ));
	obj->setScale(glm::vec3(10));
	add(obj);

	obj = GOFactory::instance()->createEmpty();
	obj->addComponent<ModelRenderComponent>()->init("../../test/mesh_test/boss1/tris.md2");
	obj->setPosition(glm::vec3(15.0f, 0.0f, 0.0f ));
	obj->setScale(glm::vec3(0.06f));
	add(obj);

	GameObject* player = GOFactory::instance()->createPlayer();
	player->setPosition(glm::vec3(0.0f, 5.0f, -5.0f));
	add(player);

	glm::ivec2 window_size = Game::instance()->getWindowSize();
	GameObject* camera = GOFactory::instance()->createPlayerCamera(player, 60.0f, 0.1f, 1000.0f, (float)window_size.x/(float)window_size.y);
	add(camera);

	AudioManager::instance()->setGlobalListener(camera);

	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));

	GameObject* ground = GOFactory::instance()->createGroundPlane();
	ground->setScale(glm::vec3(1000.0f, 1000.0f, 1000.0f));
	add(ground);

	/* */
	GameObject* sun = GOFactory::instance()->createSun(
		glm::vec3(-0.5f, -1.0f, -0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		0.2f
	);
	add(sun);

	sun = GOFactory::instance()->createSun(
		glm::vec3(0.0f, 1.0f, 0.5f),
		glm::vec3(0.0f, 0.5f, 1.0f),
		1.0f
	);
	//add(sun);
	/* */

	/* */
	float hue = 0.0f;
	float r, g, b;
	unsigned int numLights = 64;
	GameObject* lightBaseOffset = GOFactory::instance()->createEmpty();
	lightBaseOffset->setPosition(glm::vec3(-20, 0, 0));
	for (unsigned int i = 0; i < numLights; ++i) {

		if (hue < 60.0f) {
		
			r = 1.0f;
			g = hue / 60.0f;
			b = 0.0f;
		
		} else if (hue < 120.0f) {
		
			r = 1.0f - ((hue-60.0f) / 60.0f);
			g = 1.0f;
			b = 0.0f;
		
		} else if (hue < 180.0f) {
		
			r = 0.0f;
			g = 1.0f;
			b = (hue - 120.0f) / 60.0f;

		} else if (hue < 240.0f) {
		
			r = 0.0f;
			g = 1.0f - ((hue - 180.0f) / 60.0f);
			b = 1.0f;

		} else if (hue < 300.0f) {
		
			r = (hue - 240.0f) / 60.0f;
			g = 0.0f;
			b = 1.0f;

		} else {
		
			r = 1.0f;
			g = 0.0f;
			b = 1.0f - ((hue - 300.0f) / 60.0f);
		}

		hue += 360.0f / (float)numLights;

		GameObject* pl = GOFactory::instance()->createPointLight(
			glm::vec3(r, g, b),
			8.0f,
			1.0f
		);

		pl->addComponent<RandomMover>();
		lightBaseOffset->addChild(pl);
	}
	/* */
	add(lightBaseOffset);  
	GameObject* pl = GOFactory::instance()->createPointLight(glm::vec3(0, 0, 1), 15, 15);
	pl->setPosition(glm::vec3(0, 1, 5));
	add(pl);
}