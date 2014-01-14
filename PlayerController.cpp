#include "PlayerController.h"

#include "Game.h"
#include "Scene.h"
#include "GOFactory.h"
#include "Input.h"
#include "AudioManager.h"
#include "GameObjects.h"
#include "ModelRenderComponent.h"

const PlayerController::Bounds PlayerController::BOUNDS = {
	500.0f, -500.0f, //x
	 16.0f,    1.0f, //y
	500.0f, -500.0f  //z
};

const float PlayerController::LASER_INTERVAL = 0.1f;

PlayerController::PlayerController() {

	m_fMovementSpeed = 20.0f;
	m_fYawVelocity = 0.0f;
	m_fPitchVelocity = 0.0f;

	m_fPitch = 0.0f;
	m_fYaw = 0.0f;
	m_fRoll = 0.0f;
	m_fRollLimit = glm::pi<float>() * 0.5f;

	m_bJoypad = false;
	memset(m_bKeys, false, sizeof(m_bKeys));

	m_iShotsToFire = 0;
	m_fLaserTime = 0.0f;

	m_iLaserAudioID = AudioManager::instance()->loadAudio("laser.wav");
}

PlayerController::~PlayerController() {

	Scene* scene = m_xGameObject->getScene();

	scene->removeEventHandler(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	scene->removeEventHandler(Event::KEY_UP, this, &PlayerController::keyUpHandler);
	
	scene->removeEventHandler(Event::JOY_AXIS_CHANGE, this, &PlayerController::axisChangeHandler);
	scene->removeEventHandler(Event::JOY_BUTTON_DOWN, this, &PlayerController::buttonDownHandler);
	scene->removeEventHandler(Event::JOY_BUTTON_UP, this, &PlayerController::buttonUpHandler);

	Input::instance()->removeEventHandler(Event::JOY_PLUGGED_IN, this, &PlayerController::joyConnectedHandler);
	Input::instance()->removeEventHandler(Event::JOY_PLUGGED_OUT, this, &PlayerController::joyConnectedHandler);
}

void PlayerController::init(GameObject* spaceship) {

	m_xSpaceship = spaceship;

	Scene* scene = m_xGameObject->getScene();

	scene->registerEventHandler(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	scene->registerEventHandler(Event::KEY_UP, this, &PlayerController::keyUpHandler);

	Input::instance()->registerEventHandler(Event::JOY_PLUGGED_IN, this, &PlayerController::joyConnectedHandler);

	m_xGameObject->registerEventHandler(Event::COLLISION, this, &PlayerController::collisionHandler);
	scene->registerEventHandler(Event::GAME_UPDATE, this, &PlayerController::update);
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
	//m_fRoll = m_fRoll + m_fYawVelocity * 1.3f * delta - m_fRoll * 2.0f * delta;
	m_fRoll = m_fRoll + m_fYawVelocity * 0.8f * delta - m_fRoll * 2.0f * delta;

	float dist = 3.0f;
	if (position.y < BOUNDS.y_min + dist)
		m_fRollLimit = glm::pi<float>() * 0.5f * ((position.y - (BOUNDS.y_min)) / dist);
	else
		m_fRollLimit = glm::pi<float>() * 0.5f;

	getGameObject()->setRotation(glm::quat(glm::vec3(m_fPitch, m_fYaw, 0.0f))); //euler angles constructor takes radians
	m_xSpaceship->setRotation(glm::quat(glm::vec3(0.0f, 0.0f, m_fRoll * m_fRollLimit)));

	//Laser
	if (m_iShotsToFire > 0) {
	
		if (m_fLaserTime <= 0.0f) {
			
			fire();
			--m_iShotsToFire;
			m_fLaserTime = LASER_INTERVAL;
		}

		m_fLaserTime -= delta;
	}

	if (m_fCooldown > 0.0f)
		m_fCooldown -= delta;
}

void PlayerController::collisionHandler(const Event& e) {

	if (e.collision.other->getTag() != "enemy")
		return;

	glm::vec3 push(e.collision.push.x, e.collision.push.y, e.collision.push.z);

	m_xGameObject->appendPosition(push);
}

/*void PlayerController::enterStateHandler(const Event& e) {

	if (e.game.state == Game::PLAY_STATE)
		Game::instance()->registerEventHandler(Event::GAME_UPDATE, this, &PlayerController::update);
}

void PlayerController::leaveStateHandler(const Event& e) {

	if (e.game.state == Game::PLAY_STATE)
		Game::instance()->removeEventHandler(Event::GAME_UPDATE, this, &PlayerController::update);
}*/

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
			m_bKeys[FIRE] = true;
			//fire();
			activateLaser();
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

		case GLFW_KEY_X:
			m_bKeys[FIRE] = false;
			break;

		case GLFW_KEY_LEFT_SHIFT:
			m_bKeys[SLOW] = false;
			break;
		
		case GLFW_KEY_SPACE:
			m_fMovementSpeed = 20.0f;
			break;
	}
}

void PlayerController::joyConnectedHandler(const Event& e) {

	Scene* scene = m_xGameObject->getScene();

	Input::instance()->registerEventHandler(Event::JOY_PLUGGED_OUT, this, &PlayerController::joyDisconnectedHandler);

	scene->registerEventHandler(Event::JOY_AXIS_CHANGE, this, &PlayerController::axisChangeHandler);
	scene->registerEventHandler(Event::JOY_BUTTON_DOWN, this, &PlayerController::buttonDownHandler);
	scene->registerEventHandler(Event::JOY_BUTTON_UP, this, &PlayerController::buttonUpHandler);

	scene->removeEventHandler(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	scene->removeEventHandler(Event::KEY_UP, this, &PlayerController::keyUpHandler);

	memset(m_bKeys, false, sizeof(m_bKeys));

	m_bJoypad = true;
}

void PlayerController::joyDisconnectedHandler(const Event& e) {

	Scene* scene = m_xGameObject->getScene();

	Input::instance()->removeEventHandler(Event::JOY_PLUGGED_OUT, this, &PlayerController::joyDisconnectedHandler);

	scene->removeEventHandler(Event::JOY_AXIS_CHANGE, this, &PlayerController::axisChangeHandler);
	scene->removeEventHandler(Event::JOY_BUTTON_DOWN, this, &PlayerController::buttonDownHandler);
	scene->removeEventHandler(Event::JOY_BUTTON_UP, this, &PlayerController::buttonUpHandler);

	scene->registerEventHandler(Event::KEY_DOWN, this, &PlayerController::keyDownHandler);
	scene->registerEventHandler(Event::KEY_UP, this, &PlayerController::keyUpHandler);

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
			//fire();
			activateLaser();
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

void PlayerController::activateLaser() {

	if (m_fCooldown <= 0.0f) {
		
		m_iShotsToFire = SHOTS_PER_PRESS;
		m_fLaserTime = 0.0f;
		m_fCooldown = LASER_INTERVAL * (float)SHOTS_PER_PRESS - 0.05f;
	}
}

void PlayerController::fire() {
	
	Laser* laser = m_xGameObject->getScene()->make<Laser>("laser");
	laser->setPosition(m_xGameObject->getWorldPosition() + m_xGameObject->forward() * 10.0f + m_xSpaceship->right());
	laser->setRotation(m_xGameObject->getRotation());
	laser->init();

	laser = m_xGameObject->getScene()->make<Laser>("laser");
	laser->setPosition(m_xGameObject->getWorldPosition() + m_xGameObject->forward() * 10.0f - m_xSpaceship->right());
	laser->setRotation(m_xGameObject->getRotation());
	laser->init();

	AudioManager::instance()->playAudio(m_iLaserAudioID, m_xGameObject);
}