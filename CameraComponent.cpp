#include "CameraComponent.h"
#include "Camera.h"

CameraComponent::CameraComponent() : Component(CAMERA) {

}

const glm::mat4& CameraComponent::getViewMatrix() const {

	return m_xGameObject->getInverseMatrix();
}