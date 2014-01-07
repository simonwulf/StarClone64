#include "stdafx.h"

#include "OrthographicCameraComponent.h"

void OrthographicCameraComponent::init(float left, float right, float bottom, float top, float near, float far) {

	m_fLeft = left;
	m_fRight = right;
	m_fBottom = bottom;
	m_fTop = top;
	m_fNear = near;
	m_fFar = far;

	m_mProjectionMatrix = glm::ortho(m_fLeft, m_fRight, m_fBottom, m_fTop, m_fNear, m_fFar);
}

const glm::mat4& OrthographicCameraComponent::getProjectionMatrix() const {

	return m_mProjectionMatrix;
}