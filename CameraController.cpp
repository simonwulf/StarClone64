#include "CameraController.h"
#include "Game.h"

const float CameraController::DISTANCE = 5.0f;
const float CameraController::ELEVATION = 6.0f;

CameraController::CameraController() {

	m_xTarget = nullptr;

	Game::instance()->registerEventHandler<CameraController>(Event::GAME_UPDATE, this, &CameraController::update);
}

CameraController::~CameraController() {

	Game::instance()->removeEventHandler<CameraController>(Event::GAME_UPDATE, this, &CameraController::update);
}

void CameraController::init(GameObject* target) {

	m_xTarget = target;
}

void CameraController::update(const Event& e) {

	float delta = e.game.delta;

	GameObject* go = getGameObject();

	glm::vec3 target_pos = m_xTarget->getPosition() - m_xTarget->forward() * DISTANCE;
	target_pos.y = ELEVATION;
	glm::vec3 diff = target_pos - go->getPosition();

	glm::vec3 position = go->getPosition() + diff * 2.0f * delta;
	if (position.y < 0.1f)
		position.y = 0.1f;

	go->setPosition(position);

	glm::vec3 plane_forward = m_xTarget->forward();
	plane_forward.y = 0.0f;
	plane_forward = glm::normalize(plane_forward);

	glm::vec3 direction_normal = glm::cross(glm::normalize(diff), glm::vec3(0.0f, 1.0f, 0.0f));
	float target_cos = glm::dot(plane_forward, direction_normal);
	glm::vec3 look_target = m_xTarget->getPosition() + direction_normal * target_cos * 10.0f;
	look_target.y = ELEVATION;

	diff = look_target - go->getPosition();
	float angle = -atan2f(diff.x, -diff.z) * (180.0f / glm::pi<float>());
	go->setRotation(glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f)));
}