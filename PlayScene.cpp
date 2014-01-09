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

	//Test purposes
	/* Teapots */
	unsigned int count = 1;
	float dist = 5.0f;
	for (unsigned int z = 0; z < count; ++z) {
		for (unsigned int y = 0; y < count; ++y) {
			for (unsigned int x = 0; x < count; ++x) {
	
// 				float start = -dist * (float)(count-1)/2.0f;
// 
// 				GameObject* obj = GOFactory::instance()->createTeapot();
// 				obj->setPosition(
// 					glm::vec3(start, start, start) +
// 					glm::vec3(dist * x, dist * y, dist * z)
// 				);
// 				obj->setScale(glm::vec3(0.03f, 0.03f, 0.03f));
// 				
				GameObject* obj = GOFactory::instance()->createTestMesh1();
				GameObject* obj2 = GOFactory::instance()->createTestMesh2();
				GameObject* obj3 = GOFactory::instance()->createTestMesh3();
				obj3->addComponent<FMODTest>();

				obj->setPosition(glm::vec3(1, 1, -1));
				obj3->setPosition(glm::vec3(0, 4, 0));
				obj2->setPosition(glm::vec3(0, 4, 0));

				obj->setScale(glm::vec3(0.03f, 0.03f, 0.03f));
				obj3->setScale(glm::vec3(0.03f, 0.03f, 0.03f));
				obj2->setScale(glm::vec3(1));

				obj->addChild(obj2);
				obj2->setPosition(glm::vec3(0, 4, 0));

				std::stringstream ss;
				ss << "obj1: L " << obj->getPosition().x << "\t, " <<
					obj->getPosition().y << "\t, " << obj->getPosition().z << "\t\tW "
					<< obj->getWorldPosition().x << "\t, " << obj->getWorldPosition().y << 
					"\t, " << obj->getWorldPosition().z;
				ss << "\nobj2: L " << obj2->getPosition().x << "\t, " <<
					obj2->getPosition().y << "\t, " << obj2->getPosition().z << "\t\tW "
					<< obj2->getWorldPosition().x << "\t, " << obj2->getWorldPosition().y << 
					"\t, " << obj2->getWorldPosition().z;

				Log::Writeln(ss.str(), Log::COLOR_LIGHT_AQUA);

				add(obj);
				add(obj3);
				//add(obj2);
			}
		}
	}
	/* */

	GameObject* player = GOFactory::instance()->createPlayer();
	player->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
	add(player);

	glm::ivec2 window_size = Game::instance()->getWindowSize();
	GameObject* camera = GOFactory::instance()->createPlayerCamera(player, 60.0f, 0.1f, 1000.0f, (float)window_size.x/(float)window_size.y);
	add(camera);

	AudioManager::instance()->setGlobalListener(camera);

	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));

	/* */
	GameObject* sun = GOFactory::instance()->createSun(
		glm::vec3(-0.5f, -1.0f, -0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		1.0f
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