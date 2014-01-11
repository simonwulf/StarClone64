#ifndef EVENT_H
#define EVENT_H

#include <vector>

class GameObject;

class Event {

  public:

	enum Type {
	
		GAME_START,
		GAME_UPDATE,
		GAME_UPDATE_LATE,
		GAME_ENTER_STATE,
		GAME_LEAVE_STATE,

		KEY_DOWN,
		KEY_UP,

		MOUSE_DOWN,
		MOUSE_UP,
		MOUSE_MOVE,
		
		JOY_BUTTON_DOWN,
		JOY_BUTTON_UP,
		JOY_AXIS_CHANGE,
		JOY_PLUGGED_IN,
		JOY_PLUGGED_OUT,

		COLLISION,

		EVENT_N
	};

#pragma region event_type_structs
	
	struct GameEvent {
	
		float delta;
		float elapsedTime;
		unsigned int state;
	};

	struct KeyboardEvent {
		
		int charCode;
		int keyCode;
	};

	struct MouseEvent {
		
		struct {
			float x;
			float y;
		} position;
		char button;
	};

	struct JoypadEvent {
	
		unsigned int joypad;
		int button;
		int axis;
		float axisValue;
	};

	struct CollisionEvent {
	
		GameObject* other;
		struct { float x; float y; float z; } position;
		struct { float x; float y; float z; } push;
	};

#pragma endregion event_type_structs

	Event(Type type);

	union {
	
		GameEvent game;
		KeyboardEvent keyboard;
		MouseEvent mouse;
		JoypadEvent joypad;
		CollisionEvent collision;
	};

	Type type;
};

#endif