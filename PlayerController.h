#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "ControllerComponent.h"
#include "Event.h"

class PlayerController : public ControllerComponent {

  public:

	PlayerController();
	~PlayerController();

	void update(const Event& e);

	void keyDownHandler(const Event& e);
	void keyUpHandler(const Event& e);

  private:

	float m_fMovementSpeed;
	float m_fYawVelocity;
	float m_fPitchVelocity;

	float m_fPitch; //radians
	float m_fYaw; //radians
	float m_fRoll; //radians
};

#endif