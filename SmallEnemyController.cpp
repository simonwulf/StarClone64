#include "SmallEnemyController.h"

#include <random>
#include "Scene.h"
#include "GameObjects.h"
#include "AudioManager.h"

unsigned int SmallEnemyController::s_iLaserAudioID = 0;
unsigned int SmallEnemyController::s_iNumTrailing = 0;
GameObject* SmallEnemyController::s_xPlayer = nullptr;

SmallEnemyController::~SmallEnemyController() {

	if (m_bTrailing)
		--s_iNumTrailing;

	m_xGameObject->getScene()->removeEventHandler(Event::GAME_UPDATE, this, &SmallEnemyController::update);
}

void SmallEnemyController::init() {

	changeTarget();
	m_fMovementSpeed = 30.0f;
	m_fLaserCooldown = 0.0f;
	m_fTrailingCooldown = 0.0f;
	m_bTrailing = false;

	if (s_iLaserAudioID == 0)
		s_iLaserAudioID = AudioManager::instance()->loadAudio("laser.wav");

	m_xGameObject->getScene()->registerEventHandler(Event::GAME_UPDATE, this, &SmallEnemyController::update);
}

void SmallEnemyController::setPlayer(GameObject* player) {

	s_xPlayer = player;
}

void SmallEnemyController::update(const Event& e) {

	glm::vec3 diff = m_vTarget - m_xGameObject->getWorldPosition();

	if (m_bTrailing && s_xPlayer == nullptr)
		m_bTrailing = false;

	if (m_bTrailing) {

		m_fMovementSpeed += (25.0f - m_fMovementSpeed) * e.game.delta;
		m_vTarget = s_xPlayer->getWorldPosition() - s_xPlayer->forward() * 10.0f;
	
	} else {

		m_fTargetTime -= e.game.delta;

		if (glm::length(diff) < 1.0f || m_fTargetTime <= 0.0f) {
	
			changeTarget();
		}
	}

	glm::vec3 direction = glm::normalize(diff);
	glm::vec3 axis;

	float dot = glm::dot(direction, m_xGameObject->forward());
	float angle = glm::degrees(acosf(dot));
	if (angle > 90.0f * e.game.delta)
		angle = 90.0f * e.game.delta;

	if (dot < 1.0f && dot > -1.0f) {

		glm::vec3 cross = glm::cross(m_xGameObject->forward(), direction);
		
		if ((cross.x*cross.x + cross.y*cross.y + cross.z*cross.z) != 0.0f) {
			
			axis = glm::normalize(cross);

			glm::vec3 look_target = m_xGameObject->getWorldPosition() + glm::angleAxis(angle, axis) * m_xGameObject->forward();
			m_xGameObject->lookAt(look_target, glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}

	glm::vec3 position = m_xGameObject->getPosition() + m_xGameObject->forward() * m_fMovementSpeed * e.game.delta;
	if (position.y < 1.0f)
		position.y = 1.0f;

	m_xGameObject->setPosition(position);

	if (s_xPlayer == nullptr)
		return;

	diff = s_xPlayer->getWorldPosition() - m_xGameObject->getWorldPosition();
	dot = glm::dot(glm::normalize(diff), glm::normalize(m_xGameObject->forward()));
	float length_squared = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;

	if (!m_bTrailing) {
		
		m_fTrailingCooldown -= e.game.delta;

		if (m_fTrailingCooldown <= 0.0f &&
			s_iNumTrailing < MAX_TRAILING &&
			dot > 0.6f &&
			length_squared < 50.0f*50.0f) {
			
			m_bTrailing = true;
			++s_iNumTrailing;
		}
	
	} else if (dot <= 0.0f || length_squared < 12.0f*12.0f || length_squared > 80.0f*80.0f) {
	
		m_bTrailing = false;
		--s_iNumTrailing;
		m_fMovementSpeed = 30.0f;
		m_fTrailingCooldown = 5.0f;
		changeTarget();
	}

	if (m_fLaserCooldown > 0.0f)
		m_fLaserCooldown -= e.game.delta;
	else if (dot > 0.98f && length_squared < 100.0f*100.0f)
		fire();
}

void SmallEnemyController::changeTarget() {

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

void SmallEnemyController::fire() {
	
	Laser* laser = m_xGameObject->getScene()->make<Laser>("laser");
	laser->setPosition(m_xGameObject->getWorldPosition() + m_xGameObject->forward() * 10.0f);
	laser->setRotation(m_xGameObject->getRotation());
	laser->init(true);

	m_fLaserCooldown = 1.0f;

	AudioManager::instance()->playAudio(s_iLaserAudioID, m_xGameObject);
}