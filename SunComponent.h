#ifndef SUNCOMPONENT_H
#define SUNCOMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class Sun : public Component {

  public:

	Sun();
	~Sun();

  private:

	glm::vec3 m_vColor;
	float m_fIntensity;
	glm::vec3 m_vDirection;
};

#endif