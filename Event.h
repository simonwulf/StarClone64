#ifndef EVENT_H
#define EVENT_H

#include <vector>

class Event {

  public:

	enum Type {
	
		GAME_START,
		GAME_UPDATE,

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

class EventDispatcher {

  public:

	virtual ~EventDispatcher();

	template <class T>
	void registerEventHandler(Event::Type type, T* context, void (T::*handler)(const Event&)) {

		for (unsigned int i = 0; i < m_xHandlers[type].size(); ++i) {
			if (((EventHandler<T>*)m_xHandlers[type][i])->handles(context, handler))
				return;
		}

		m_xHandlers[type].push_back(new EventHandler<T>(context, handler));
	}

	template <class T>
	void removeEventHandler(Event::Type type, T* context, void (T::*handler)(const Event&)) {
	
		for (unsigned int i = 0; i < m_xHandlers[type].size(); ++i) {
			if (((EventHandler<T>*)m_xHandlers[type][i])->handles(context, handler)) {
				
				delete m_xHandlers[type][i];
				m_xHandlers[type].erase(m_xHandlers[type].begin() + i);
				return;
			}
		}
	}

	void dispatchEvent(const Event& e) {
	
		for (unsigned int i = 0; i < m_xHandlers[e.type].size(); ++i) {
			m_xHandlers[e.type][i]->handle(e);
		}
	}

  private:

	class AbstractEventHandler {
	  
	  public:

		virtual void handle(const Event& e) = 0;
	};

	template <class T>
	class EventHandler : public AbstractEventHandler {
	
	  public:

		EventHandler(T* context, void (T::*handler)(const Event&)) {

			m_xContext = context;
			m_xHandler = handler;
		}

		void handle(const Event& e) {
		
			(m_xContext->*m_xHandler)(e);
		}

		bool handles(T* context, void (T::*handler)(const Event&)) {
		
			return m_xContext == context && m_xHandler == handler;
		}

	  private:

		T* m_xContext;
		void (T::*m_xHandler)(const Event&);
	};

	typedef std::vector<AbstractEventHandler*> HandlerList;
	HandlerList m_xHandlers[Event::EVENT_N];
};

#endif