#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include <glm/core/type_mat4x4.hpp>

class CameraComponent : public Component {

  public:

	CameraComponent();

	virtual const glm::mat4& getProjectionMatrix() const = 0;
	const glm::mat4& getViewMatrix() const;
};

#endif