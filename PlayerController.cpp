#include "PlayerController.h"

#include "Game.h"
#include "GOFactory.h"
#include "Input.h"
#include "AudioManager.h"

const PlayerController::Bounds PlayerController::BOUNDS = {
	500.0f, -500.0f, //x
	 16.0f,    1.0f, //y
	500.0f, -500.0f  //z
};

PlayerController::PlayerController() {

	Input::instance()->registerEventHandler(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	Input::instance()->registerEventHandler(Event::KEY_UP, this, &PlayerController::keyUpHandler);

	Input::instance()->registerEventHandler(Event::JOY_PLUGGED_IN, this, &PlayerController::joyConnectedHandler);

	Game::instance()->registerEventHandler(Event::GAME_ENTER_STATE, this, &PlayerController::enterStateHandler);
	Game::instance()->registerEventHandler(Event::GAME_LEAVE_STATE, this, &PlayerController::leaveStateHandler);

	m_fMovementSpeed = 20.0f;
	m_fYawVelocity = 0.0f;
	m_fPitchVelocity = 0.0f;

	m_fPitch = 0.0f;
	m_fYaw = 0.0f;
	m_fRoll = 0.0f;

	m_bJoypad = false;
	memset(m_bKeys, false, sizeof(m_bKeys));

	m_iLaserAudioID = AudioManager::instance()->loadAudio("laser.wav");
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

	if (!m_bJoypad) {
	
		m_fPitchVelocity = 0.0f;
		m_fYawVelocity = 0.0f;
		m_fMovementSpeed = 20.0f;

		if (m_bKeys[UP])
			m_fPitchVelocity -= 1.0f;
		if (m_bKeys[RIGHT])
			m_fYawVelocity -= 1.0f;
		if (m_bKeys[DOWN])
			m_fPitchVelocity += 1.0f;
		if (m_bKeys[LEFT])
			m_fYawVelocity += 1.0f;
		if (m_bKeys[SLOW])
			m_fMovementSpeed *= 0.5f;
	}

	glm::vec3 position = go->getPosition();
	glm::vec3 velocity = go->forward() * m_fMovementSpeed * delta;

	position += velocity;

	if (position.x < BOUNDS.x_min)
		position.x = BOUNDS.x_min;
	else if (position.x > BOUNDS.x_max)
		position.x = BOUNDS.x_max;

	if (position.y < BOUNDS.y_min) {
		
		position.y = BOUNDS.y_min;
		if (m_fPitchVelocity < 0.0f)
			m_fPitchVelocity = 0.0f;
		m_fPitch = m_fPitch - m_fPitch * 4.0f * delta;

	} else if (position.y > BOUNDS.y_max) {
		
		position.y += (BOUNDS.y_max - position.y) * 5.0f * delta;
	}

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

void PlayerController::enterStateHandler(const Event& e) {

	if (e.game.state == Game::PLAY_STATE)
		Game::instance()->registerEventHandler(Event::GAME_UPDATE, this, &PlayerController::update);
}

void PlayerController::leaveStateHandler(const Event& e) {

	if (e.game.state == Game::PLAY_STATE)
		Game::instance()->removeEventHandler(Event::GAME_UPDATE, this, &PlayerController::update);
}

void PlayerController::keyDownHandler(const Event& e) {

	switch (e.keyboard.charCode) {
	
		case GLFW_KEY_UP:
			m_bKeys[UP] = true;
			break;

		case GLFW_KEY_RIGHT:
			m_bKeys[RIGHT] = true;
			break;

		case GLFW_KEY_LEFT:
			m_bKeys[LEFT] = true;
			break;

		case GLFW_KEY_DOWN:
			m_bKeys[DOWN] = true;
			break;

		case GLFW_KEY_LEFT_SHIFT:
			m_bKeys[SLOW] = true;
			break;

		case GLFW_KEY_X:
			fire();
			break;
	}
}

void PlayerController::keyUpHandler(const Event& e) {

	switch (e.keyboard.charCode) {
	
		case GLFW_KEY_UP:
			m_bKeys[UP] = false;
			break;

		case GLFW_KEY_RIGHT:
			m_bKeys[RIGHT] = false;
			break;

		case GLFW_KEY_LEFT:
			m_bKeys[LEFT] = false;
			break;

		case GLFW_KEY_DOWN:
			m_bKeys[DOWN] = false;
			break;

		case GLFW_KEY_LEFT_SHIFT:
			m_bKeys[SLOW] = false;
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

	memset(m_bKeys, false, sizeof(m_bKeys));

	m_bJoypad = true;
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

	m_bJoypad = false;
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
			fire();
			break;

		case 1: //Circle
			break;

		case 2: //Square
			break;

		case 3: //Triangle
			break;

		case 7: //Start
			Game::instance()->pause();
			break;
	}
}

void PlayerController::buttonUpHandler(const Event& e) {

}

void PlayerController::fire() {

	if (Game::instance()->getState() != Game::PLAY_STATE)
		return;
	
	GameObject* laser = GOFactory::instance()->createLaser();
	laser->setPosition(m_xGameObject->getWorldPosition() + m_xGameObject->forward() * 8.0f + m_xSpaceship->right());
	laser->setRotation(m_xGameObject->getRotation());
	m_xGameObject->getScene()->add(laser);

	laser = GOFactory::instance()->createLaser();
	laser->setPosition(m_xGameObject->getWorldPosition() + m_xGameObject->forward() * 8.0f - m_xSpaceship->right());
	laser->setRotation(m_xGameObject->getRotation());
	m_xGameObject->getScene()->add(laser);

	AudioManager::instance()->playAudio(m_iLaserAudioID, m_xGameObject);
}