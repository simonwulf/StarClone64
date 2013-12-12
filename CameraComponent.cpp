#include "CameraComponent.h"
#include "Camera.h"

CameraComponent::CameraComponent() : Component(Component::Type::CAMERA) {

	//This does not belong here, move camera selection to Camera class
	if (Camera::s_xMainCamera == nullptr) {
	
		Camera::s_xMainCamera = this;
		Camera::currentCamera = this;
	}
}

CameraComponent::~CameraComponent() {

	//This does not belong here, move camera selection to Camera class
	if (Camera::s_xMainCamera == this)
		Camera::s_xMainCamera = nullptr;

	if (Camera::currentCamera == this)
		Camera::currentCamera = Camera::s_xMainCamera;
}

const glm::mat4& CameraComponent::getMatrix() {

	return getGameObject()->getInverseMatrix();
}