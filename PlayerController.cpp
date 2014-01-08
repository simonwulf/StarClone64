#include "PlayerController.h"
#include "Game.h"

const PlayerController::Bounds PlayerController::BOUNDS = {
	500.0f, -500.0f, //x
	 12.0f,    1.0f, //y
	500.0f, -500.0f  //z
};

PlayerController::PlayerController() {

	Game::instance()->registerEventHandler<PlayerController>(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Game::instance()->registerEventHandler<PlayerController>(Event::KEY_UP, this, &PlayerController::keyUpHandler);
	Game::instance()->registerEventHandler<PlayerController>(Event::GAME_UPDATE, this, &PlayerController::update);

	m_fMovementSpeed = 20.0f;
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

void PlayerController::init(GameObject* spaceship) {

	m_xSpaceship = spaceship;
}

void PlayerController::update(const Event& e) {

	float delta = e.game.delta;

	GameObject* go = getGameObject();

	glm::vec3 position = go->getPosition();
	glm::vec3 velocity = go->forward() * m_fMovementSpeed * delta;

	position += velocity;

	if (position.x < BOUNDS.x_min)
		position.x = BOUNDS.x_min;
	else if (position.x > BOUNDS.x_max)
		position.x = BOUNDS.x_max;

	if (position.y < BOUNDS.y_min)
		position.y = BOUNDS.y_min;
	else if (position.y > BOUNDS.y_max)
		position.y += (BOUNDS.y_max - position.y) * 5.0f * delta;

	if (position.z < BOUNDS.z_min)
		position.z = BOUNDS.z_min;
	else if (position.z > BOUNDS.z_max)
		position.z = BOUNDS.z_max;

	go->setPosition(position);
	
	m_fYaw += m_fYawVelocity * delta;
	m_fPitch = m_fPitch + m_fPitchVelocity * 1.5f * delta - m_fPitch * 2.0f * delta;
	m_fRoll = m_fRoll + m_fYawVelocity * delta - m_fRoll * 2.0f * delta;

	getGameObject()->setRotation(glm::quat(glm::vec3(m_fPitch, m_fYaw, 0.0f))); //euler angles constructor takes radians
	m_xSpaceship->setRotation(glm::quat(glm::vec3(0.0f, 0.0f, m_fRoll)));
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

		case GLFW_KEY_LEFT_SHIFT:
			m_fMovementSpeed = 10.0f;
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

		case GLFW_KEY_LEFT_SHIFT:
			m_fMovementSpeed = 20.0f;
			break;
	}
}

float PlayerController::getYawVelocity() const {

	return m_fYawVelocity;
}