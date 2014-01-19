#ifndef PERSPECTIVECAMERACOMPONENT_H
#define PERSPECTIVECAMERACOMPONENT_H

#include "CameraComponent.h"

#undef near
#undef far

class Visitor;

class PerspectiveCameraComponent : public CameraComponent {

  public:

	void init(float fov, float near, float far, float ratio);

	void accept(Visitor* visitor);

	const glm::mat4& getProjectionMatrix() const;

	float getFov() const;
	float getNear() const;
	float getFar() const;
	float getRatio() const;

	void setFov(float value);
	void setNear(float value);
	void setFar(float value);
	void setRatio(float value);

  private:

	float m_fFov;
	float m_fNear;
	float m_fFar;
	float m_fRatio;

	glm::mat4 m_mProjectionMatrix;
};

#endif