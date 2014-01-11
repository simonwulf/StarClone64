#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "ControllerComponent.h"
#include "Event.h"

class CameraController : public ControllerComponent {

  public:

	CameraController();
	~CameraController();

	void init(GameObject* target);

  private:

	static const float DISTANCE;
	static const float ELEVATION;

	GameObject* m_xTarget;

	void update(const Event& e);

	void enterStateHandler(const Event& e);
	void leaveStateHandler(const Event& e);
};

#endif