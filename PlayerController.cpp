#include "PlayerController.h"
#include "Game.h"

PlayerController::PlayerController() {

	Game::instance()->registerEventHandler<PlayerController>(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Game::instance()->registerEventHandler<PlayerController>(Event::KEY_UP, this, &PlayerController::keyUpHandler);
	Game::instance()->registerEventHandler<PlayerController>(Event::GAME_UPDATE, this, &PlayerController::update);

	m_fMovementSpeed = 3.0f;
	m_fYawVelocity = 0.0f;
	m_fPitchVelocity = 0.0f;

	m_fPitch = 0.0f;
	m_fYaw = 0.0f;
	m_fRoll = 0.0f;
}

PlayerController::~PlayerController() {

	Game::instance()->removeEventHandler<PlayerController>(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Game::instance()->removeEventHandler<PlayerController>(Event::KEY_UP, this, &PlayerController::keyUpHandler);
	Game::instance()->removeEventHandler<PlayerController>(Event::GAME_UPDATE, this, &PlayerController::update);
}

//void PlayerController::update(float delta, float elapsedTime) {
void PlayerController::update(const Event& e) {

	float delta = e.game.delta;

	getGameObject()->appendPosition(glm::vec3(getGameObject()->forward() * m_fMovementSpeed * delta));
	
	m_fYaw += m_fYawVelocity * delta;
	m_fPitch = m_fPitch + m_fPitchVelocity * 1.5f * delta - m_fPitch * 2.0f * delta;

	getGameObject()->setRotation(glm::quat(glm::vec3(m_fPitch, m_fYaw, m_fRoll))); //euler angles constructor takes radians
}

void PlayerController::keyDownHandler(const Event& e) {

	switch (e.keyboard.charCode) {
	
		case GLFW_KEY_UP:
			m_fPitchVelocity -= 1.0f;
			break;

		case GLFW_KEY_RIGHT:
			m_fYawVelocity -= 1.0f;
			break;

		case GLFW_KEY_LEFT:
			m_fYawVelocity += 1.0f;
			break;

		case GLFW_KEY_DOWN:
			m_fPitchVelocity += 1.0f;
			break;
	}
}

void PlayerController::keyUpHandler(const Event& e) {

	switch (e.keyboard.charCode) {
	
		case GLFW_KEY_UP:
			m_fPitchVelocity += 1.0f;
			break;

		case GLFW_KEY_RIGHT:
			m_fYawVelocity += 1.0f;
			break;

		case GLFW_KEY_LEFT:
			m_fYawVelocity -= 1.0f;
			break;

		case GLFW_KEY_DOWN:
			m_fPitchVelocity -= 1.0f;
			break;
	}
}