#include "CameraController.h"
#include "Game.h"

const float CameraController::DISTANCE = 5.0f;

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
	glm::vec3 diff = target_pos - go->getPosition();

	go->appendPosition(diff * 2.0f * delta);

	glm::mat4 view = glm::lookAt(
		go->getPosition(),
		m_xTarget->getPosition() + m_xTarget->forward() * 5.0f,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	go->setMatrix(glm::inverse(view)); //glm::lookAt returns a view matrix, so we need the inverse lookAt matrix to get the cameras orientation in world space. Kind of messy and unoptimized, but works
}