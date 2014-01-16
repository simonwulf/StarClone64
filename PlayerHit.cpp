#include "PlayerHit.h"

#include "AudioManager.h"
#include "HUDModel.h"

unsigned int PlayerHit::s_iHitAudioID = 0;

PlayerHit::~PlayerHit() {

	m_xGameObject->removeEventHandler(Event::COLLISION, this, &PlayerHit::collisionHandler);
}

void PlayerHit::init(unsigned int hp) {

	m_iMaxHP = hp;
	m_iHP = hp;

	m_xGameObject->registerEventHandler(Event::COLLISION, this, &PlayerHit::collisionHandler);

	if (s_iHitAudioID == 0)
		s_iHitAudioID = AudioManager::instance()->loadAudio("hit.wav");
}

void PlayerHit::collisionHandler(const Event& e) {

	if (e.collision.other->getTag() == "laser") {

		m_iHP -= 10;

		HUDModel::instance()->setHPFactor((float)m_iHP / (float)m_iMaxHP);

		if (m_iHP == 0) {
			
			m_xGameObject->destroy();
			AudioManager::instance()->playAudio(s_iHitAudioID, m_xGameObject);
		}

		AudioManager::instance()->playAudio(s_iHitAudioID, m_xGameObject);
	}
}