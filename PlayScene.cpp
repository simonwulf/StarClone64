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

	setAmbientLight(glm::vec3(0.5f, 0.5f, 0.5f));
	setClearFlags(GL_DEPTH_BUFFER_BIT);

	GameObject* obj = GOFactory::instance()->createTeapot();
 	obj->setPosition(glm::vec3(0.0f));
 	obj->setScale(glm::vec3(0.03f, 0.03f, 0.03f));

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
		0.5f
	);
	add(sun);

	sun = GOFactory::instance()->createSun(
		glm::vec3(0.0f, 1.0f, 0.5f),
		glm::vec3(0.0f, 0.5f, 1.0f),
		1.0f
	);
	add(sun);
	/* */

	/* *
	float hue = 0.0f;
	float r, g, b;
	unsigned int numLights = 64;

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
		add(pl);
	}
	/* */
}