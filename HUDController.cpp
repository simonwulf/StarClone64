#include "HUDController.h"
#include "HUDModel.h"

#include "GUITextureRenderComponent.h"

HUDController::HUDController() {

	m_xWinText = nullptr;
	m_xLoseText = nullptr;

	HUDModel::instance()->registerEventHandler(Event::HUD_UPDATE, this, &HUDController::update);
}

HUDController::~HUDController() {

	HUDModel::instance()->removeEventHandler(Event::HUD_UPDATE, this, &HUDController::update);
}

void HUDController::init(GameObject* healthBar, GameObject* winText, GameObject* loseText) {

	m_xHealthBar = healthBar;

	m_xWinText = static_cast<GUITextureRenderComponent*>(winText->getComponent(Component::RENDER));
	m_xLoseText = static_cast<GUITextureRenderComponent*>(loseText->getComponent(Component::RENDER));

	m_xWinText->setVisible(false);
	m_xLoseText->setVisible(false);
}

void HUDController::update(const Event& e) {

	m_xHealthBar->setScale(glm::vec3(
		HUDModel::instance()->getHPFactor(),
		1.0f,
		1.0f
	));

	m_xWinText->setVisible(HUDModel::instance()->getScore() == 64);
	m_xLoseText->setVisible(HUDModel::instance()->getHPFactor() <= 0.0f);
}