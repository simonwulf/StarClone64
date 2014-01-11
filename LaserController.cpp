#include "LaserController.h"

#include "Game.h"
#include "GOFactory.h"

LaserController::LaserController() {

	m_fLifeTime = 1.0f;

	if (Game::instance()->getState() == Game::PLAY_STATE)
		Game::instance()->registerEventHandler(Event::GAME_UPDATE, this, &LaserController::update);

	Game::instance()->registerEventHandler(Event::GAME_ENTER_STATE, this, &LaserController::enterStateHandler);
	Game::instance()->registerEventHandler(Event::GAME_LEAVE_STATE, this, &LaserController::leaveStateHandler);
}

LaserController::~LaserController() {

	Game::instance()->removeEventHandler(Event::GAME_UPDATE, this, &LaserController::update);
	Game::instance()->removeEventHandler(Event::GAME_ENTER_STATE, this, &LaserController::enterStateHandler);
	Game::instance()->removeEventHandler(Event::GAME_LEAVE_STATE, this, &LaserController::leaveStateHandler);
}

void LaserController::update(const Event& e) {

	m_fLifeTime -= e.game.delta;

	if (m_fLifeTime <= 0.0f || m_xGameObject->getPosition().y < 0.0f) {
	
		GOFactory::instance()->destroy(m_xGameObject);
		return;
	}

	m_xGameObject->setScale(glm::vec3(1.0f, 1.0f, 1.0f + 4.0f * m_fLifeTime));
	m_xGameObject->appendPosition(m_xGameObject->forward() * (300.0f * e.game.delta));
}

void LaserController::enterStateHandler(const Event& e) {

	if (e.game.state == Game::PLAY_STATE)
		Game::instance()->registerEventHandler(Event::GAME_UPDATE, this, &LaserController::update);
}

void LaserController::leaveStateHandler(const Event& e) {

	if (e.game.state == Game::PLAY_STATE)
		Game::instance()->removeEventHandler(Event::GAME_UPDATE, this, &LaserController::update);
}