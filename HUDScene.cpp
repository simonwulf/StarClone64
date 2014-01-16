#include "HUDScene.h"

#include "Game.h"
#include "GameObjects.h"
#include "HUDController.h"
#include "GUITextureRenderComponent.h"

HUDScene::HUDScene() {

	m_xGameObjectFactory.registerCreator<GameObject>("empty");
	m_xGameObjectFactory.registerCreator<GUICamera>("camera");
	m_xGameObjectFactory.registerCreator<GUITexture>("gui_texture");

	glm::ivec2 w_size = Game::instance()->getWindowSize();
	GUICamera* camera = make<GUICamera>("camera");
	camera->init((float)w_size.x, (float)w_size.y);

	useCamera((CameraComponent*)camera->getComponent(Component::CAMERA));

	GUITexture* hpBack = make<GUITexture>("gui_texture");
	hpBack->init("data/gui/hp_back.png");
	hpBack->setPosition(glm::vec3(20.0f, 20.0f, 0.0f));

	GUITexture* hpFront = make<GUITexture>("gui_texture");
	hpFront->init("data/gui/hp_front.png");
	hpFront->setPosition(glm::vec3(23.0f, 23.0f, 1.0f));

	GUITexture* winText = make<GUITexture>("gui_texture");
	winText->init("data/gui/win.png");
	GUITextureRenderComponent* rc = static_cast<GUITextureRenderComponent*>(winText->getComponent(Component::RENDER));
	winText->setPosition(glm::vec3(
		(float)w_size.x * 0.5f - rc->getTexture()->getSize().x * 0.5f,
		(float)w_size.y * 0.5f - rc->getTexture()->getSize().y * 0.5f,
		0.0f
	));

	GUITexture* loseText = make<GUITexture>("gui_texture");
	loseText->init("data/gui/lose.png");
	rc = static_cast<GUITextureRenderComponent*>(loseText->getComponent(Component::RENDER));
	loseText->setPosition(glm::vec3(
		(float)w_size.x * 0.5f - rc->getTexture()->getSize().x * 0.5f,
		(float)w_size.y * 0.5f - rc->getTexture()->getSize().y * 0.5f,
		0.0f
	));

	GameObject* hudController = make("empty");
	hudController->addComponent<HUDController>()->init(hpFront, winText, loseText);

	setAmbientLight(glm::vec3(1.0f, 1.0f, 1.0f));
	setClearFlags(GL_DEPTH_BUFFER_BIT);
}