#ifndef LASERCONTROLLER_H
#define LASERCONTROLLER_H

#include "ControllerComponent.h"
#include "Event.h"

class LaserController : public ControllerComponent {

  public:

	LaserController();
	~LaserController();

  private:

	float m_fLifeTime;

	void update(const Event& e);
};

#endif