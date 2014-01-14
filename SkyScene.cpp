#include "SkyScene.h"
#include "GOFactory.h"
#include "Game.h"

#include "GameObjects.h"

SkyScene::SkyScene() {

	setAmbientLight(glm::vec3(1));

	m_xGameObjectFactory.registerCreator<Skybox>("skybox");
	m_xGameObjectFactory.registerCreator<SkyCamera>("camera");

	make<Skybox>("skybox")->init();
}

void SkyScene::init( GameObject* camRef ) {

	glm::ivec2 window_size = Game::instance()->getWindowSize();
	SkyCamera* camera = make<SkyCamera>("camera");
	camera->init(camRef, 60.0f, 0.1f, 1000.0f, (float)window_size.x/(float)window_size.y);
	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));
}