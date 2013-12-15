#include "PointLightComponent.h"

PointLightComponent::PointLightComponent() : LightComponent(Component::POINT_LIGHT) {

	m_fRadius = 10.0f;
	m_vColor = glm::vec3(1.0f);
	m_fStrength = 1.0f;
}

PointLightComponent::~PointLightComponent() {

}

void PointLightComponent::setRadius(float radius) {

	m_fRadius = radius;
}

void PointLightComponent::setColor(glm::vec3 color) {

	m_vColor = color;
}

void PointLightComponent::setStrength(float strength) {

	m_fStrength = strength;
}

float PointLightComponent::getRadius() const {

	return m_fRadius;
}

glm::vec3 PointLightComponent::getColor() const {

	return m_vColor;
}

float PointLightComponent::getStrength() const {

	return m_fStrength;
}

void PointLightComponent::glData(float* dst) {

	glm::vec4 global_position = getGameObject()->getMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	memcpy(dst, &global_position, sizeof(float) * 3);
	memcpy(dst + 3, &m_fRadius, sizeof(float) * 5);
}