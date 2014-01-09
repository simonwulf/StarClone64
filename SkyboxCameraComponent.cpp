#include "SkyboxCameraComponent.h"
#include "Game.h"
#include "LogManager.h"

SkyboxCameraComponent::SkyboxCameraComponent() : Component(Component::Type::CAMERA) {
	
	refObject = nullptr;
}

void SkyboxCameraComponent::lateUpdate(const Event& e) {

	if(refObject != nullptr) {

		//this->getGameObject()->setPosition(refObject->getPosition() * this->getGameObject()->getScale());
		this->getGameObject()->setRotation(refObject->getRotation());
	}
}

void SkyboxCameraComponent::init( GameObject* refObj ) {

	Game::instance()->registerEventHandler(Event::GAME_UPDATE, this, &SkyboxCameraComponent::lateUpdate);
	refObject = refObj;
}
