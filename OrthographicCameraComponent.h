#ifndef ORTHOGRAPHICCAMERACOMPONENT_H
#define ORTHOGRAPHICCAMERACOMPONENT_H

#include <glm/core/type_mat4x4.hpp>

#include "CameraComponent.h"

#undef near
#undef far

class OrthographicCameraComponent : public CameraComponent {

  public:

	void init(float left, float right, float bottom, float top, float near, float far);

	const glm::mat4& getProjectionMatrix() const;

	void setLeft(float value);
	void setRight(float value);
	void setBottom(float value);
	void setTop(float value);
	void setNear(float value);
	void setFar(float value);

	float getLeft() const;
	float getRight() const;
	float getBottom() const;
	float getTop() const;
	float getNear() const;
	float getFar() const;

  private:

	float m_fLeft;
	float m_fRight;
	float m_fBottom;
	float m_fTop;
	float m_fNear;
	float m_fFar;

	glm::mat4 m_mProjectionMatrix;
};

#endif