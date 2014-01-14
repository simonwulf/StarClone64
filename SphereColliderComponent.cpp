#include "SphereColliderComponent.h"

SphereColliderComponent::SphereColliderComponent() : ColliderComponent(ColliderComponent::SPHERE) {

	m_fRadius = 0.0f;
}

void SphereColliderComponent::init(float radius) {

	m_fRadius = radius;
}

RaycastResult SphereColliderComponent::raycast(Ray ray) {

	RaycastResult result;

	glm::vec3 center = m_xGameObject->getWorldPosition();

	glm::vec3 diff = center - ray.start;
	glm::vec3 diff_projected = (glm::dot(diff, ray.direction) / glm::dot(ray.direction, ray.direction)) * ray.direction;

	float diff_length = glm::length(diff);
	float diff_projected_length = glm::length(diff_projected);

	float disc = m_fRadius*m_fRadius - (diff_length*diff_length - diff_projected_length*diff_projected_length);
	float scalar = 0.0f;
	float dot;

	if (disc >= 0.0f) {
		scalar = diff_projected_length - sqrtf(disc);
		dot = glm::dot(ray.direction, diff_projected);
	}

	if (disc >= 0.0f && dot >= 0.0f && (ray.infinite || scalar <= glm::length(ray.direction))) { //Hit

		result.gameObject = m_xGameObject;
		result.position = ray.start + glm::normalize(ray.direction) * scalar;
		result.normal = glm::normalize(result.position - center);
		result.hit = true;

	} else {
	
		result.gameObject = nullptr;
		result.hit = false;
	}

	return result;
}

float SphereColliderComponent::getRadius() {

	return m_fRadius;
}