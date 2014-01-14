#include "SkyboxCameraComponent.h"
#include "Game.h"
#include "LogManager.h"

SkyboxCameraComponent::SkyboxCameraComponent() : Component(CAMERA) {
	
	refObject = nullptr;
}

void SkyboxCameraComponent::lateUpdate(const Event& e) {

	if(refObject != nullptr) {

		//this->getGameObject()->setPosition(refObject->getPosition() * this->getGameObject()->getScale());
		this->getGameObject()->setRotation(refObject->getRotation());
	}
}

void SkyboxCameraComponent::init( GameObject* refObj ) {

	m_xGameObject->getScene()->registerEventHandler(Event::GAME_UPDATE_LATE, this, &SkyboxCameraComponent::lateUpdate);
	refObject = refObj;
}
