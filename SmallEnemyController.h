#ifndef SMALLENEMYCONTROLLER_H
#define SMALLENEMYCONTROLLER_H

#include "ControllerComponent.h"

class SmallEnemyController : public ControllerComponent {

public:

	~SmallEnemyController();

	void init();

	static void setPlayer(GameObject* player);

private:

	static const unsigned int MAX_TRAILING = 3;

	glm::vec3 m_vTarget;
	float m_fMovementSpeed;
	float m_fTargetTime;
	float m_fLaserCooldown;
	float m_fTrailingCooldown;

	static unsigned int s_iLaserAudioID;
	static unsigned int s_iNumTrailing;
	static GameObject* s_xPlayer;

	bool m_bTrailing;

	void update(const Event& e);

	void changeTarget();

	void fire();
};

#endif