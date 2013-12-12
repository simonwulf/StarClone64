#ifndef CAMERA_H
#define CAMERA_H

#include "CameraComponent.h"

class Camera {

  public:

	static CameraComponent* currentCamera;

  private:

	Camera() {};

	static CameraComponent* s_xMainCamera;

	friend CameraComponent::CameraComponent();
	friend CameraComponent::~CameraComponent();
};

#endif