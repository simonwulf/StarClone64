#include "LaserController.h"

#include "Game.h"
#include "Scene.h"
#include "AudioManager.h"

unsigned int LaserController::s_iHitAudioID = 0;

LaserController::LaserController() {

	m_fLifeTime = 1.0f;

	if (s_iHitAudioID == 0)
		s_iHitAudioID = AudioManager::instance()->loadAudio("hit.wav");

	//if (Game::instance()->getState() == Game::PLAY_STATE)
	//	Game::instance()->registerEventHandler(Event::GAME_UPDATE, this, &LaserController::update);

	//Game::instance()->registerEventHandler(Event::GAME_ENTER_STATE, this, &LaserController::enterStateHandler);
	//Game::instance()->registerEventHandler(Event::GAME_LEAVE_STATE, this, &LaserController::leaveStateHandler);
}

LaserController::~LaserController() {

	//Game::instance()->removeEventHandler(Event::GAME_UPDATE, this, &LaserController::update);
	//Game::instance()->removeEventHandler(Event::GAME_ENTER_STATE, this, &LaserController::enterStateHandler);
	//Game::instance()->removeEventHandler(Event::GAME_LEAVE_STATE, this, &LaserController::leaveStateHandler);

	m_xGameObject->getScene()->removeEventHandler(Event::GAME_UPDATE, this, &LaserController::update);
}

void LaserController::init() {

	m_xGameObject->getScene()->registerEventHandler(Event::GAME_UPDATE, this, &LaserController::update);

	m_xRay.direction = m_xGameObject->forward() * 10.0f;
	m_xRay.start = m_xGameObject->getWorldPosition() - m_xRay.direction;
	m_xRay.infinite = false;

	rayTest();
}

void LaserController::update(const Event& e) {

	m_fLifeTime -= e.game.delta;

	m_xGameObject->setScale(glm::vec3(1.0f, 1.0f, 1.0f + 4.0f * m_fLifeTime));

	glm::vec3 movement = m_xGameObject->forward() * (300.0f * e.game.delta);

	m_xRay.start = m_xGameObject->getWorldPosition();
	m_xRay.direction = movement;

	rayTest();

	m_xGameObject->appendPosition(movement);

	if (m_fLifeTime <= 0.0f)
		m_xGameObject->destroy();

	if (m_xGameObject->getPosition().y < 0.0f) {
		m_xGameObject->destroy();
		AudioManager::instance()->playAudio(s_iHitAudioID, m_xGameObject);
	}
}

void LaserController::rayTest() {

	RaycastResult result = m_xGameObject->getScene()->raycast(m_xRay);

	if (result.hit && result.gameObject->getTag() == "enemy") {
	
		AudioManager::instance()->playAudio(s_iHitAudioID, result.position);

		m_xGameObject->destroy();

		Event e(Event::COLLISION);
		e.collision.other = m_xGameObject;
		e.collision.position.x = result.position.x;
		e.collision.position.y = result.position.y;
		e.collision.position.z = result.position.z;
		e.collision.push.x = 0.0f;
		e.collision.push.y = 0.0f;
		e.collision.push.z = 0.0f;

		result.gameObject->dispatchEvent(e);
	}
}

/*void LaserController::enterStateHandler(const Event& e) {

	if (e.game.state == Game::PLAY_STATE)
		Game::instance()->registerEventHandler(Event::GAME_UPDATE, this, &LaserController::update);
}

void LaserController::leaveStateHandler(const Event& e) {

	if (e.game.state == Game::PLAY_STATE)
		Game::instance()->removeEventHandler(Event::GAME_UPDATE, this, &LaserController::update);
}*/