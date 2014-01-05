#ifndef EVENT_H
#define EVENT_H

#include <vector>

class Event {

  public:

	enum Type {
	
		GAME_START,
		GAME_UPDATE,
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

	struct JoyButtonEvent {
	
		unsigned int joypad;
		unsigned int button;
	};

	struct JoyAxisEvent {
	
		unsigned int joypad;
		unsigned int axis;
		float value;
	};

#pragma endregion event_type_structs

	Event(Type type);

	union {
	
		GameEvent game;
		KeyboardEvent keyboard;
		MouseEvent mouse;
		JoyButtonEvent joyButton;
		JoyAxisEvent joyAxis;
	};

	Type type;
};

#endif