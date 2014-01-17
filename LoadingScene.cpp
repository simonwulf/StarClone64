#include "LoadingScene.h"
#include "Game.h"
#include "PerspectiveCameraComponent.h"

LoadingScene::LoadingScene() {

	setAmbientLight(glm::vec3(1));
	setClearFlags(GL_DEPTH_BUFFER_BIT);

	m_xGameObjectFactory.registerCreator<GameObject>("empty");
	glm::ivec2 window_size = Game::instance()->getWindowSize();
	GameObject* camera = make("empty");
	camera->addComponent<PerspectiveCameraComponent>()->init(60.0f, 0.01f, 1000.0f, (float)window_size.x/(float)window_size.y);
	camera->setPosition(glm::vec3(0.0f));

	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));
}