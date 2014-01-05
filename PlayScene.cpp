#include "PlayScene.h"
#include "GOFactory.h"

#include "CameraComponent.h"
#include "CameraController.h"
#include "RandomMover.h"
#include "ModelRenderComponent.h"

PlayScene::PlayScene() {

	//Test purposes
	/* Teapots */
	unsigned int count = 1;
	float dist = 5.0f;
	for (unsigned int z = 0; z < count; ++z) {
		for (unsigned int y = 0; y < count; ++y) {
			for (unsigned int x = 0; x < count; ++x) {
	
				float start = -dist * (float)(count-1)/2.0f;

				GameObject* obj = GOFactory::instance()->createTeapot();
				obj->setPosition(
					glm::vec3(start, start, start) +
					glm::vec3(dist * x, dist * y, dist * z)
				);
				
				add(obj);
			}
		}
	}
	/* */

	GameObject* player = GOFactory::instance()->createPlayer();
	player->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
	add(player);

	GameObject* camera = GOFactory::instance()->createEmpty();
	//m_xTestCam->setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	camera->addComponent<CameraComponent>();
	camera->addComponent<CameraController>()->init(player);
	add(camera);

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