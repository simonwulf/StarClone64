#include "SmallEnemyMovement.h"

#include <random>
#include <iostream>
#include "Scene.h"

SmallEnemyMovement::~SmallEnemyMovement() {

	m_xGameObject->getScene()->removeEventHandler(Event::GAME_UPDATE, this, &SmallEnemyMovement::update);
}

void SmallEnemyMovement::init() {

	changeTarget();
	m_fMovementSpeed = 30.0f;

	m_xGameObject->getScene()->registerEventHandler(Event::GAME_UPDATE, this, &SmallEnemyMovement::update);
}

void SmallEnemyMovement::update(const Event& e) {

	glm::vec3 diff = m_vTarget - m_xGameObject->getWorldPosition();

	m_fTargetTime -= e.game.delta;

	if (glm::length(diff) < 1.0f || m_fTargetTime <= 0.0f) {
	
		changeTarget();
	}

	glm::vec3 direction = glm::normalize(diff);
	glm::vec3 axis;

	float dot = glm::dot(direction, m_xGameObject->forward());
	float angle = glm::degrees(acosf(dot));
	if (angle > 90.0f * e.game.delta)
		angle = 90.0f * e.game.delta;

	if (dot < 1.0f && dot > -1.0f) {

		axis = glm::normalize(glm::cross(m_xGameObject->forward(), direction));

		glm::vec3 look_target = m_xGameObject->getWorldPosition() + glm::angleAxis(angle, axis) * m_xGameObject->forward();
		m_xGameObject->lookAt(look_target, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 position = m_xGameObject->getPosition() + m_xGameObject->forward() * m_fMovementSpeed * e.game.delta;
	if (position.y < 1.0f)
		position.y = 1.0f;

	m_xGameObject->setPosition(position);
}

void SmallEnemyMovement::changeTarget() {

	float u = (float)rand() / (float)RAND_MAX + (float)rand() / (float)RAND_MAX;
	float t = 2.0f * glm::pi<float>() * (float)rand() / (float)RAND_MAX;
	float r = u > 1.0f ? 2.0f - u : u;
	
	m_vTarget = glm::vec3(
		r*cosf(t) * 250.0f,
		((float)rand() / (float)RAND_MAX) * 24.0f + 6.0f,
		r*sinf(t) * 250.0f
	);

	m_fTargetTime = 4.0f + ((float)rand() / (float)RAND_MAX) * 2.0f;
}