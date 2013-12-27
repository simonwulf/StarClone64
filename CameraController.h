#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "ControllerComponent.h"
#include "Event.h"

class CameraController : public ControllerComponent {

  public:

	CameraController();
	~CameraController();

	void init(GameObject* target);

	void update(const Event& e);

  private:

	static const float DISTANCE;

	GameObject* m_xTarget;
};

#endif