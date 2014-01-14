#include "EnemyHit.h"
#include "LogManager.h"
#include "AudioManager.h"

unsigned int EnemyHit::s_iSplosionAudioID = 0;

EnemyHit::~EnemyHit() {

	m_xGameObject->removeEventHandler(Event::COLLISION, this, &EnemyHit::collisionHandler);
}

void EnemyHit::init(unsigned int hp) {

	m_iHP = hp;

	m_xGameObject->registerEventHandler(Event::COLLISION, this, &EnemyHit::collisionHandler);

	if (s_iSplosionAudioID == 0)
		s_iSplosionAudioID = AudioManager::instance()->loadAudio("splosion.wav");
}

void EnemyHit::collisionHandler(const Event& e) {

	if (e.collision.other->getTag() == "laser") {
	
		--m_iHP;

		if (m_iHP == 0) {
			
			m_xGameObject->destroy();
			AudioManager::instance()->playAudio(s_iSplosionAudioID, m_xGameObject);
		}
	}
}