#include "ControllerComponent.h"

ControllerComponent::ControllerComponent() : Component(Component::CONTROLLER) {

}

ControllerComponent::~ControllerComponent() {

}

void ControllerComponent::move(const glm::vec3& distance) {

	getGameObject()->setPosition(getGameObject()->getPosition() + distance);

	//TODO: collision
}