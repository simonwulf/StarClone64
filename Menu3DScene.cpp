#include "Menu3DScene.h"
#include "PerspectiveCameraComponent.h"
#include "Game.h"
#include "AudioManager.h"
#include "GameObjects.h"

Menu3DScene::Menu3DScene() {

	setAmbientLight(glm::vec3(0.5f));
	setClearFlags(GL_DEPTH_BUFFER_BIT);
	glm::ivec2 window_size = Game::instance()->getWindowSize();

	m_xGameObjectFactory.registerCreator<GameObject>("empty");

	GameObject* camera = make("empty");
	camera->addComponent<PerspectiveCameraComponent>()->init(60.0f, 0.01f, 1000.0f, (float)window_size.x/(float)window_size.y);

	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));

	AudioManager::instance()->setGlobalListener(camera);
}