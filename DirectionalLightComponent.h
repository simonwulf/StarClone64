#ifndef DIRECTIONALLIGHTCOMPONENT_H
#define DIRECTIONALLIGHTCOMPONENT_H

#include "LightComponent.h"
#include <glm/glm.hpp>

class DirectionalLightComponent : public LightComponent {

  public:

	DirectionalLightComponent();
	virtual ~DirectionalLightComponent();

	void setDirection(const glm::vec3& direction);
	void setColor(const glm::vec3& color);
	void setStrength(float strength);

	glm::vec3 getDirection() const;
	glm::vec3 getColor() const;
	float getStrength() const;

	void glData(float* dst);

  private:

	glm::vec3 m_vDirection;
	glm::vec3 m_vColor;
	float m_fStrength;
};

#endif