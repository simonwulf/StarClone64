#ifndef POINTLIGHTCOMPONENT_H
#define POINTLIGHTCOMPONENT_H

#include "stdafx.h"
#include "LightComponent.h"

class PointLightComponent : public LightComponent {

  public:

	PointLightComponent();
	~PointLightComponent();

	void init(float radius, glm::vec3 color, float strength);

	void setRadius(float radius);
	void setColor(glm::vec3 color);
	void setStrength(float strength);

	float getRadius() const;
	glm::vec3 getColor() const;
	float getStrength() const;

	void glData(float* dst);

private:

	float m_fRadius;
	glm::vec3 m_vColor;
	float m_fStrength;
};

#endif