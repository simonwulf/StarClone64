#include "SkyScene.h"
#include "GOFactory.h"
#include "Game.h"

#include "GameObjects.h"

SkyScene::SkyScene() {

	setAmbientLight(glm::vec3(1));

	m_xGameObjectFactory.registerCreator<Skybox>("skybox");
	m_xGameObjectFactory.registerCreator<SkyCamera>("camera");

	make<Skybox>("skybox")->init();

	glm::ivec2 window_size = Game::instance()->getWindowSize();
	m_xCamera = make<SkyCamera>("camera");
	m_xCamera->init(60.0f, 0.1f, 1000.0f, (float)window_size.x/(float)window_size.y);
	useCamera(static_cast<CameraComponent*>(m_xCamera->getComponent(Component::CAMERA)));
}

void SkyScene::setReference( GameObject* camRef ) {

	m_xCamera->setReference(camRef);
}