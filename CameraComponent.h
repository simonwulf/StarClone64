#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class CameraComponent : public Component {

  public:

	CameraComponent();
	~CameraComponent();

	const glm::mat4& getMatrix();

  private:

	float m_fFov;
	float m_fNear;
	float m_fFar;
	float m_fRatio;

	glm::mat4x4 m_mPerspectiveMatrix;
};

#endif