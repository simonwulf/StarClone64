#include "DirectionalLightComponent.h"
#include <iostream>

DirectionalLightComponent::DirectionalLightComponent() : LightComponent(DIRECTIONAL_LIGHT) {

}

DirectionalLightComponent::~DirectionalLightComponent() {

}

void DirectionalLightComponent::setDirection(const glm::vec3& direction) {

	m_vDirection = direction;
}

void DirectionalLightComponent::setColor(const glm::vec3& color) {

	m_vColor = color;
}

void DirectionalLightComponent::setStrength(float strength) {

	m_fStrength = strength;
}

glm::vec3 DirectionalLightComponent::getDirection() const {

	return m_vDirection;
}

glm::vec3 DirectionalLightComponent::getColor() const {

	return m_vColor;
}

float DirectionalLightComponent::getStrength() const {

	return m_fStrength;
}

void DirectionalLightComponent::glData(float* dst) {

	glm::vec4 transformed = getGameObject()->getMatrix() * glm::vec4(m_vDirection, 0.0f);

	//std::cout << transformed.x << ", " << transformed.y << ", " << transformed.z << std::endl;

	memcpy(dst, &transformed, sizeof(float) * 4);
	memcpy(dst + 4, &m_vColor, sizeof(float) * 4);
}