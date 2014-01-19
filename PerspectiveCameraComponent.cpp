#include "stdafx.h"

#include "PerspectiveCameraComponent.h"
#include "Visitor.h"

void PerspectiveCameraComponent::init(float fov, float near, float far, float ratio) {

	m_fFov = fov;
	m_fNear = near;
	m_fFar = far;
	m_fRatio = ratio;

	m_mProjectionMatrix = glm::perspective(fov, m_fRatio, near, far);
}

void PerspectiveCameraComponent::accept(Visitor* visitor) {

	visitor->visitPerspectiveCameraComponent(this);
}

const glm::mat4& PerspectiveCameraComponent::getProjectionMatrix() const {

	return m_mProjectionMatrix;
}

float PerspectiveCameraComponent::getFov() const {

	return m_fFov;
}

float PerspectiveCameraComponent::getNear() const {

	return m_fNear;
}

float PerspectiveCameraComponent::getFar() const {

	return m_fFar;
}

float PerspectiveCameraComponent::getRatio() const {

	return m_fRatio;
}

void PerspectiveCameraComponent::setFov(float value) {

	m_fFov = value;
}

void PerspectiveCameraComponent::setNear(float value) {

	m_fNear = value;
}

void PerspectiveCameraComponent::setFar(float value) {

	m_fFar = value;
}

void PerspectiveCameraComponent::setRatio(float value) {

	m_fRatio = value;
}