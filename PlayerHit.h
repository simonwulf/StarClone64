#ifndef PLAYERHIT_H
#define PLAYERHIT_H

#include "Component.h"
#include "Event.h"

class PlayerHit : public Component {

  public:

	~PlayerHit();

	void init(unsigned int hp = 1);

  private:

	void collisionHandler(const Event& e);

	unsigned int m_iMaxHP;
	unsigned int m_iHP;
	float m_fHitCooldown;
	static unsigned int s_iHitAudioID;
};

#endif