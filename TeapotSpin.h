#ifndef TEAPOTSPIN_H
#define TEAPOTSPIN_H

#include "ControllerComponent.h"
#include "Event.h"

class TeapotSpin : public ControllerComponent {

  public:

	TeapotSpin();
	~TeapotSpin();

	void update(const Event& e);
};

#endif