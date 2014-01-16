#include "GameState.h"
#include "Renderer.h"

#include "CollisionManager.h"

GameState::GameState() {

}

GameState::~GameState() {

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		delete m_xScenes[i];
	}
}

void GameState::addScene(Scene* scene) {

	m_xScenes.push_back(scene);
}

void GameState::update(float delta, float elapsedTime) {

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		if (m_xScenes[i]->isActive())
			m_xScenes[i]->update(delta, elapsedTime);
	}

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		if (m_xScenes[i]->isActive())
			CollisionManager::checkCollisions(m_xScenes[i]);
	}

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		if (m_xScenes[i]->isActive())
			m_xScenes[i]->lateUpdate(delta, elapsedTime);
	}

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		if (m_xScenes[i]->isActive())
			m_xScenes[i]->removeDead();
	}
}

void GameState::render(Renderer* renderer) {

	for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		renderer->render(m_xScenes[i]);
	}
}