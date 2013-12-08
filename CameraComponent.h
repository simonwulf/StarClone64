#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class Camera : public Component {

  public:

	Camera();
	~Camera();

  private:

	float m_fFov;
	float m_fNear;
	float m_fFar;
	float m_fRatio;

	glm::mat4x4 m_mPerspectiveMatrix;
};

#endif