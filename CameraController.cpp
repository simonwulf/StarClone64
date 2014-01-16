#include "CameraController.h"
#include "Game.h"

const float CameraController::DISTANCE = 5.0f;
const float CameraController::ELEVATION = 8.0f;

CameraController::CameraController() {

	m_xTarget = nullptr;

	//Game::instance()->registerEventHandler(Event::GAME_ENTER_STATE, this, &CameraController::enterStateHandler);
	//Game::instance()->registerEventHandler(Event::GAME_LEAVE_STATE, this, &CameraController::leaveStateHandler);
}

CameraController::~CameraController() {

	m_xGameObject->getScene()->removeEventHandler(Event::GAME_UPDATE, this, &CameraController::update);

	if (m_xTarget != nullptr)
		m_xTarget->removeEventHandler(Event::GAMEOBJECT_DESTROYED, this, &CameraController::targetDestroyed);
}

void CameraController::init(GameObject* target) {

	m_xTarget = target;

	m_xGameObject->getScene()->registerEventHandler(Event::GAME_UPDATE, this, &CameraController::update);
	m_xTarget->registerEventHandler(Event::GAMEOBJECT_DESTROYED, this, &CameraController::targetDestroyed);
}

void CameraController::update(const Event& e) {

	if (m_xTarget == nullptr)
		return;

	float delta = e.game.delta;

	GameObject* go = getGameObject();

	glm::vec3 plane_forward = m_xTarget->forward();
	plane_forward.y = 0.0f;
	plane_forward = glm::normalize(plane_forward);

	glm::vec3 direction_normal = glm::cross(glm::normalize(m_xTarget->getPosition() - go->getPosition()), glm::vec3(0.0f, 1.0f, 0.0f));
	float target_cos = glm::dot(plane_forward, direction_normal);

	glm::vec3 target_pos = m_xTarget->getPosition() - m_xTarget->forward() * DISTANCE;
	target_pos.y = ELEVATION + (target_pos.y - ELEVATION) * 0.7f;
	glm::vec3 diff = target_pos - go->getPosition();

	glm::vec3 position = go->getPosition() + diff * 2.0f * delta;
	if (position.y < 0.1f)
		position.y = 0.1f;

	go->setPosition(position);

	glm::vec3 look_target = m_xTarget->getPosition() + direction_normal * target_cos * 10.0f;
	look_target.y = ELEVATION + (look_target.y - ELEVATION) * 0.5f;

	m_xGameObject->lookAt(look_target, glm::vec3(0.0f, 1.0f, 0.0f));
}

void CameraController::targetDestroyed(const Event& e) {

	m_xTarget = nullptr;
}