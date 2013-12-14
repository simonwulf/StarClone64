#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H

#include "Component.h"

class ControllerComponent : public Component {

  public:

	ControllerComponent();
	virtual ~ControllerComponent();

  protected:

	void move(const glm::vec3& distance);
};

#endif