#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "ControllerComponent.h"
#include "Event.h"

class PlayerController : public ControllerComponent {

  public:

	PlayerController();
	~PlayerController();

	void init(GameObject* spaceship);

  private:

	static const struct Bounds {
	
		float x_max;
		float x_min;
		float y_max;
		float y_min;
		float z_max;
		float z_min;

	} BOUNDS;

	enum Key {
	
		UP,
		RIGHT,
		DOWN,
		LEFT,
		FIRE,
		SLOW,

		KEY_N
	};

	float m_fMovementSpeed;
	float m_fYawVelocity;
	float m_fPitchVelocity;

	float m_fPitch; //radians
	float m_fYaw; //radians
	float m_fRoll; //radians

	bool m_bJoypad;
	bool m_bKeys[KEY_N];

	unsigned int m_iLaserAudioID;

	GameObject* m_xSpaceship;

	void fire();

	void update(const Event& e);

	void enterStateHandler(const Event& e);
	void leaveStateHandler(const Event& e);

	void keyDownHandler(const Event& e);
	void keyUpHandler(const Event& e);

	void axisChangeHandler(const Event& e);
	void buttonDownHandler(const Event& e);
	void buttonUpHandler(const Event& e);

	void joyConnectedHandler(const Event& e);
	void joyDisconnectedHandler(const Event& e);
};

#endif