#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "ControllerComponent.h"
#include "Event.h"

class PlayerController : public ControllerComponent {

  public:

	PlayerController();
	~PlayerController();

	void update(float delta, float elapsedTime);

	void keyDownHandler(const Event& e);
	void keyUpHandler(const Event& e);

  private:

	glm::vec3 m_vVelocity;
};

#endif