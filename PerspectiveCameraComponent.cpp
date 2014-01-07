#include "stdafx.h"

#include "PerspectiveCameraComponent.h"

#undef near
#undef far

void PerspectiveCameraComponent::init(float fov, float near, float far, float ratio) {

	m_fFov = fov;
	m_fNear = near;
	m_fFar = far;
	m_fRatio = ratio;

	m_mProjectionMatrix = glm::perspective(fov, m_fRatio, near, far);
}

const glm::mat4& PerspectiveCameraComponent::getProjectionMatrix() const {

	return m_mProjectionMatrix;
}