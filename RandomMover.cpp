#include "stdafx.h"

#include "RandomMover.h"

#include "Game.h"

RandomMover::RandomMover() {

	updateTarget();

	m_fSpeed = 10.0f;

	Game::instance()->registerEventHandler<RandomMover>(Event::GAME_UPDATE, this, &RandomMover::update);
}

RandomMover::~RandomMover() {

}

void RandomMover::update(const Event& e) {

	float delta = e.game.delta;

	GameObject* go = getGameObject();

	glm::vec3 diff = m_vTarget - go->getPosition();

	if (glm::length(diff) <= m_fSpeed * delta) {
	
		go->setPosition(m_vTarget);
		updateTarget();

	} else {
	
		go->setPosition(go->getPosition() + glm::normalize(diff) * m_fSpeed * delta);
	}
}

void RandomMover::updateTarget() {

	m_vTarget.x = (((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f) * 25.0f;
	m_vTarget.y = (((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f) * 25.0f;
	m_vTarget.z = (((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f) * 25.0f;
}