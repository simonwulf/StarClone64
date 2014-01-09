#include "PlayerController.h"

#include "Game.h"
#include "GOFactory.h"
#include "Input.h"

const PlayerController::Bounds PlayerController::BOUNDS = {
	500.0f, -500.0f, //x
	 12.0f,    1.0f, //y
	500.0f, -500.0f  //z
};

PlayerController::PlayerController() {

	Input::instance()->registerEventHandler(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Input::instance()->registerEventHandler(Event::KEY_UP, this, &PlayerController::keyUpHandler);

	Input::instance()->registerEventHandler(Event::JOY_PLUGGED_IN, this, &PlayerController::joyConnectedHandler);

	Game::instance()->registerEventHandler(Event::GAME_UPDATE, this, &PlayerController::update);

	m_fMovementSpeed = 20.0f;
	m_fYawVelocity = 0.0f;
	m_fPitchVelocity = 0.0f;

	m_fPitch = 0.0f;
	m_fYaw = 0.0f;
	m_fRoll = 0.0f;
}

PlayerController::~PlayerController() {

	Input::instance()->removeEventHandler(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Input::instance()->removeEventHandler(Event::KEY_UP, this, &PlayerController::keyUpHandler);
	
	Input::instance()->removeEventHandler(Event::JOY_AXIS_CHANGE, this, &PlayerController::axisChangeHandler);
	Input::instance()->removeEventHandler(Event::JOY_BUTTON_DOWN, this, &PlayerController::buttonDownHandler);
	Input::instance()->removeEventHandler(Event::JOY_BUTTON_UP, this, &PlayerController::buttonUpHandler);

	Game::instance()->removeEventHandler(Event::GAME_UPDATE, this, &PlayerController::update);
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
	m_fRoll = m_fRoll + m_fYawVelocity * 1.3f * delta - m_fRoll * 2.0f * delta;

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

void PlayerController::joyConnectedHandler(const Event& e) {

	Input::instance()->registerEventHandler(Event::JOY_PLUGGED_OUT, this, &PlayerController::joyDisconnectedHandler);

	Input::instance()->registerEventHandler(Event::JOY_AXIS_CHANGE, this, &PlayerController::axisChangeHandler);
	Input::instance()->registerEventHandler(Event::JOY_BUTTON_DOWN, this, &PlayerController::buttonDownHandler);
	Input::instance()->registerEventHandler(Event::JOY_BUTTON_UP, this, &PlayerController::buttonUpHandler);

	Input::instance()->removeEventHandler(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Input::instance()->removeEventHandler(Event::KEY_UP, this, &PlayerController::keyUpHandler);
}

void PlayerController::joyDisconnectedHandler(const Event& e) {

	Input::instance()->removeEventHandler(Event::JOY_PLUGGED_OUT, this, &PlayerController::joyDisconnectedHandler);

	Input::instance()->removeEventHandler(Event::JOY_AXIS_CHANGE, this, &PlayerController::axisChangeHandler);
	Input::instance()->removeEventHandler(Event::JOY_BUTTON_DOWN, this, &PlayerController::buttonDownHandler);
	Input::instance()->removeEventHandler(Event::JOY_BUTTON_UP, this, &PlayerController::buttonUpHandler);

	Input::instance()->registerEventHandler(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Input::instance()->registerEventHandler(Event::KEY_UP, this, &PlayerController::keyUpHandler);

	m_fYawVelocity = 0.0f;
	m_fPitchVelocity = 0.0f;
	m_fMovementSpeed = 20.0f;
}

void PlayerController::axisChangeHandler(const Event& e) {

	switch (e.joypad.axis) {
	
		case 0: //X-axis
			m_fYawVelocity = -e.joypad.axisValue;
			if (abs(m_fYawVelocity) < 0.01f)
				m_fYawVelocity = 0.0f;
			break;

		case 1: //Y-axis
			m_fPitchVelocity = e.joypad.axisValue < 0.0f ?
				  e.joypad.axisValue*e.joypad.axisValue :
				-(e.joypad.axisValue*e.joypad.axisValue);
			if (abs(m_fPitchVelocity) < 0.01f)
				m_fPitchVelocity = 0.0f;
			break;

		case 2: //Analog triggers
			if (abs(e.joypad.axisValue) > 0.9f)
				m_fMovementSpeed = 10.0f;
			else
				m_fMovementSpeed = 20.0f;
			break;
	}
}

void PlayerController::buttonDownHandler(const Event& e) {

	switch (e.joypad.button) {
	
		case 0: //Cross
			{
				GameObject* laser = GOFactory::instance()->createLaser();
				laser->setPosition(m_xGameObject->getWorldPosition() + m_xGameObject->forward() * 8.0f);
				laser->setRotation(m_xGameObject->getRotation());
				m_xGameObject->getScene()->add(laser);
			}
			break;

		case 1: //Circle
			break;

		case 2: //Square
			break;

		case 3: //Triangle
			break;
	}
}

void PlayerController::buttonUpHandler(const Event& e) {

}