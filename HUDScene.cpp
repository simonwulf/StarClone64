#include "HUDScene.h"

#include "GOFactory.h"
#include "Game.h"

HUDScene::HUDScene() {

	glm::ivec2 w_size = Game::instance()->getWindowSize();
	GameObject* camera = GOFactory::instance()->createGUICamera((float)w_size.x, (float)w_size.y);
	add(camera);

	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));

	GameObject* guiTest = GOFactory::instance()->createGUITest();
	add(guiTest);

	guiTest->setPosition(glm::vec3(20.0f, 20.0f, 0.0f));

	setAmbientLight(glm::vec3(1.0f, 1.0f, 1.0f));
	setClearFlags(GL_DEPTH_BUFFER_BIT);
}