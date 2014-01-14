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

	/*if (glm::length(diff) < 1.0f) {
	
		changeTarget();
	}*/

	glm::vec3 direction = glm::normalize(diff);
	glm::vec3 axis;

	float dot = glm::dot(direction, m_xGameObject->forward());
	float angle = glm::degrees(acosf(dot));
	if (angle > 90.0f * e.game.delta);
		angle == 90.0f * e.game.delta;

	//std::cout << "dot: " << dot << ", angle: " << angle << std::endl;

	if (dot != 1.0f) {

		if (dot == -1.0f)
			axis = glm::vec3(0.0f, 1.0f, 0.0f);
		else
			axis = glm::normalize(glm::cross(direction, m_xGameObject->forward()));

		glm::vec3 look_target = m_xGameObject->getWorldPosition() + glm::angleAxis(angle, axis) * m_xGameObject->forward();
		m_xGameObject->lookAt(look_target, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	m_xGameObject->appendPosition(m_xGameObject->forward() * m_fMovementSpeed * e.game.delta);
}

void SmallEnemyMovement::changeTarget() {

	float u = (float)rand() / (float)RAND_MAX + (float)rand() / (float)RAND_MAX;
	float t = 2.0f * glm::pi<float>() * (float)rand() / (float)RAND_MAX;
	float r = u > 1.0f ? 2.0f - u : u;
	
	//sf::Vector2f(r*cos(t), r*sin(t)) * m_fRadius;
	m_vTarget = glm::vec3(
		r*cosf(t) * 250.0f,
		((float)rand() / (float)RAND_MAX) * 29.0f + 1.0f,
		r*sinf(t) * 250.0f
	);

	//m_xGameObject->lookAt(m_vTarget, glm::vec3(0.0f, 1.0f, 0.0f));
}