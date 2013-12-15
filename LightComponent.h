#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include "Component.h"

class LightComponent : public Component {

  public:

	LightComponent(Component::Type type);

	virtual void glData(float* dst) = 0;
};

#endif