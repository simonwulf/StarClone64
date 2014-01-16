#include "SkyboxCameraComponent.h"
#include "Game.h"
#include "LogManager.h"

SkyboxCameraComponent::SkyboxCameraComponent() : Component(CONTROLLER) {
	
	refObject = nullptr;
}

SkyboxCameraComponent::~SkyboxCameraComponent() {

	m_xGameObject->getScene()->removeEventHandler(Event::GAME_UPDATE_LATE, this, &SkyboxCameraComponent::lateUpdate);
}

void SkyboxCameraComponent::lateUpdate(const Event& e) {

	if(refObject != nullptr) {

		//this->getGameObject()->setPosition(refObject->getPosition() * this->getGameObject()->getScale());
		this->getGameObject()->setRotation(refObject->getRotation());
	}
}

void SkyboxCameraComponent::init() {

	m_xGameObject->getScene()->registerEventHandler(Event::GAME_UPDATE_LATE, this, &SkyboxCameraComponent::lateUpdate);
}

void SkyboxCameraComponent::setReference(GameObject* refObj) {

	refObject = refObj;
}