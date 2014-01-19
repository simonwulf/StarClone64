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
#include "GameObjects.h"
#include "SmallEnemyController.h"
#include "HUDModel.h"

PlayScene::PlayScene() {

	setAmbientLight(glm::vec3(0.3f, 0.3f, 0.3f));
	setClearFlags(GL_DEPTH_BUFFER_BIT);
	
	m_xGameObjectFactory.registerCreator<GameObject>("empty");
	m_xGameObjectFactory.registerCreator<Player>("player");
	m_xGameObjectFactory.registerCreator<PlayerCamera>("camera");
	m_xGameObjectFactory.registerCreator<Laser>("laser");
	m_xGameObjectFactory.registerCreator<SimpleModel>("model");
	m_xGameObjectFactory.registerCreator<Sun>("sun");
	m_xGameObjectFactory.registerCreator<PointLight>("pointlight");
	m_xGameObjectFactory.registerCreator<SmallEnemy>("small_enemy");

	HUDModel::instance()->reset();

	Player* player = make<Player>("player");
	player->setPosition(glm::vec3(0.0f, 6.0f, 0.0f));
	player->init();

	player->registerEventHandler(Event::GAMEOBJECT_DESTROYED, this, &PlayScene::playerKilled);

	glm::ivec2 window_size = Game::instance()->getWindowSize();
	PlayerCamera* camera = make<PlayerCamera>("camera");
	camera->init(player, 60.0f, 0.1f, 1000.0f, (float)window_size.x/(float)window_size.y);

	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));

	AudioManager::instance()->setGlobalListener(camera);

	/*SimpleModel* teapot = make<SimpleModel>("model");
	teapot->init("../../test/mesh_test/boss1/tris.md2");
 	teapot->setPosition(glm::vec3(0.0f));
 	teapot->setScale(glm::vec3(0.03f, 0.03f, 0.03f));*/

	for (unsigned int i = 0; i < 64; ++i) {
		
		SmallEnemy* enemy = make<SmallEnemy>("small_enemy");
		enemy->setPosition(glm::vec3(
			((float)rand() / (float)RAND_MAX) * 500.0f - 250.0f,
			((float)rand() / (float)RAND_MAX) * 6.0f + 3.0f,
			((float)rand() / (float)RAND_MAX) * 500.0f - 250.0f
		));
		enemy->init();
	}

	SmallEnemyController::setPlayer(player);

	SimpleModel* ground = make<SimpleModel>("model");
	ground->init("terrain/terrain_test.obj");
	ground->setScale(glm::vec3(1000.0f, 1000.0f, 1000.0f));

	/* */
	make<Sun>("sun")->init(
		glm::vec3(-0.5f, -1.0f, -0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		0.5f
	);

	make<Sun>("sun")->init(
		glm::vec3(0.0f, 1.0f, 0.5f),
		glm::vec3(0.0f, 0.5f, 1.0f),
		1.0f
	);
	/* */

	/* DISCO *
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

		PointLight* pl = make<PointLight>("pointlight");
		pl->init(
			glm::vec3(r, g, b),
			8.0f,
			1.0f
		);

		pl->addComponent<RandomMover>();
	}
	/* */

	registerEventHandler(Event::GAME_UPDATE, this, &PlayScene::update);
}

void PlayScene::update(const Event& e) {

	if (m_fEndTime > 0.0f) {
	
		m_fEndTime -= e.game.delta;

		if (m_fEndTime <= 0.0f) {
			
			Game::instance()->setState(Game::MENU_STATE);
		}
	}
}

void PlayScene::playerKilled(const Event& e) {

	SmallEnemyController::setPlayer(nullptr);

	m_fEndTime = 5.0f;
}