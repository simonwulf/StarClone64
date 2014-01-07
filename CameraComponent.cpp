#include "CameraComponent.h"
#include "Camera.h"

CameraComponent::CameraComponent() : Component(Component::Type::CAMERA) {

}

const glm::mat4& CameraComponent::getViewMatrix() const {

	return m_xGameObject->getInverseMatrix();
}