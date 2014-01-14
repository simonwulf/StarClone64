#ifndef ENEMYHIT_H
#define ENEMYHIT_H

#include "Component.h"
#include "Event.h"

class EnemyHit : public Component {

  public:

	~EnemyHit();

	void init(unsigned int hp = 1);

  private:

	void collisionHandler(const Event& e);

	unsigned int m_iHP;
	static unsigned int s_iSplosionAudioID;
};

#endif