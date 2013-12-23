#include "PlayerController.h"
#include "Game.h"

PlayerController::PlayerController() {

	Game::instance()->addHandler<PlayerController>(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Game::instance()->addHandler<PlayerController>(Event::KEY_UP, this, &PlayerController::keyUpHandler);
}

PlayerController::~PlayerController() {

	Game::instance()->removeHandler<PlayerController>(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Game::instance()->removeHandler<PlayerController>(Event::KEY_UP, this, &PlayerController::keyUpHandler);
}

void PlayerController::update(float delta, float elapsedTime) {

	getGameObject()->appendPosition(m_vVelocity * (5.0f * delta));
}

void PlayerController::keyDownHandler(const Event& e) {

	switch (e.keyboard.charCode) {
	
		case GLFW_KEY_UP:
			m_vVelocity.z -= 1.0f;
			break;

		case GLFW_KEY_RIGHT:
			m_vVelocity.x += 1.0f;
			break;

		case GLFW_KEY_LEFT:
			m_vVelocity.x -= 1.0f;
			break;

		case GLFW_KEY_DOWN:
			m_vVelocity.z += 1.0f;
			break;
	}
}

void PlayerController::keyUpHandler(const Event& e) {

	switch (e.keyboard.charCode) {
	
		case GLFW_KEY_UP:
			m_vVelocity.z += 1.0f;
			break;

		case GLFW_KEY_RIGHT:
			m_vVelocity.x -= 1.0f;
			break;

		case GLFW_KEY_LEFT:
			m_vVelocity.x += 1.0f;
			break;

		case GLFW_KEY_DOWN:
			m_vVelocity.z -= 1.0f;
			break;
	}
}