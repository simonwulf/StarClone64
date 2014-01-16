#ifndef LASERCONTROLLER_H
#define LASERCONTROLLER_H

#include "ControllerComponent.h"
#include "Event.h"
#include "RayCast.h"

class LaserController : public ControllerComponent {

  public:

	LaserController();
	~LaserController();

	void init(bool enemy);

  private:

	float m_fLifeTime;
	Ray m_xRay;

	static unsigned int s_iHitAudioID;

	void update(const Event& e);

	void rayTest();

	//void enterStateHandler(const Event& e);
	//void leaveStateHandler(const Event& e);
};

#endif