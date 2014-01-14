#include "HUDScene.h"

#include "Game.h"
#include "GameObjects.h"

HUDScene::HUDScene() {

	m_xGameObjectFactory.registerCreator<GUICamera>("camera");
	m_xGameObjectFactory.registerCreator<GUITexture>("gui_texture");

	glm::ivec2 w_size = Game::instance()->getWindowSize();
	GUICamera* camera = make<GUICamera>("camera");
	camera->init((float)w_size.x, (float)w_size.y);

	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));

	GUITexture* guiTest = make<GUITexture>("gui_texture");
	guiTest->init("test/GUItest.png");
	guiTest->setPosition(glm::vec3(20.0f, 20.0f, 0.0f));

	setAmbientLight(glm::vec3(1.0f, 1.0f, 1.0f));
	setClearFlags(GL_DEPTH_BUFFER_BIT);
}