#include "MenuGUIScene.h"
#include "Game.h"
#include "MainMenuController.h"
#include "PerspectiveCameraComponent.h"
#include "GameObjects.h"
#include "AudioManager.h"

MenuGUIScene::MenuGUIScene() {

	setAmbientLight(glm::vec3(0.5f));
	setClearFlags(GL_DEPTH_BUFFER_BIT);
	glm::ivec2 window_size = Game::instance()->getWindowSize();

	m_xGameObjectFactory.registerCreator<GameObject>("empty");
	m_xGameObjectFactory.registerCreator<MainMenu>("menu");
	m_xGameObjectFactory.registerCreator<PointLight>("pointlight");

	GameObject* camera = make("empty");
	camera->addComponent<PerspectiveCameraComponent>()->init(60.0f, 0.01f, 1000.0f, (float)window_size.x/(float)window_size.y);
	camera->setPosition(glm::vec3(0.0f, 0.0f, 7.0f));
	
	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));

	//GameObject* mainMenu = GOFactory::instance()->createMainMenu();
	//add(mainMenu);
	make<MainMenu>("menu")->init();

// 	glm::ivec2 w_size = Game::instance()->getWindowSize();
// 	GameObject* camera = GOFactory::instance()->createGUICamera((float)w_size.x, (float)w_size.y);
// 	add(camera);
// 	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));
// 
// 	GameObject* mainMenu = GOFactory::instance()->createMainMenu();
// 	add(mainMenu);
// 	((MainMenuController*)mainMenu->getComponent(Component::CONTROLLER))->init();

	setAmbientLight(glm::vec3(1.0f, 1.0f, 1.0f));
	setClearFlags(GL_DEPTH_BUFFER_BIT);
	AudioManager::instance()->playMusic("music01.mp3");
}