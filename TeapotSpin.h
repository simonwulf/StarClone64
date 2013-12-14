#ifndef TEAPOTSPIN_H
#define TEAPOTSPIN_H

#include "ControllerComponent.h"

class TeapotSpin : public ControllerComponent {

  public:

	TeapotSpin();
	~TeapotSpin();

	void update(float delta, float deltaTime);
};

#endif