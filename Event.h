#ifndef EVENT_H
#define EVENT_H

#include <vector>

/**
 * Event system
 *
 * I'm doing some weird stuff here, converting between void pointers
 * and method pointers. The internet says that this is bad practice
 * and could lead to undefined behaviour, but it seems to be working fine
 * to me. A safer approach could be taken if we only allow one handler per
 * event type per object. //Simon
 **/

class Event {

  public:

	enum Type {
	
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

	union {
	
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
	void addHandler(Event::Type type, T* context, void (T::*handler)(const Event&)) {

		for (unsigned int i = 0; i < m_xHandlers[type].size(); ++i) {
			if (m_xHandlers[type][i]->handles(context, *(void**)&handler))
				return;
		}

		m_xHandlers[type].push_back(new EventHandler<T>(context, handler));
	}

	template <class T>
	void removeHandler(Event::Type type, T* context, void (T::*handler)(const Event&)) {
	
		for (unsigned int i = 0; i < m_xHandlers[type].size(); ++i) {
			if (m_xHandlers[type][i]->handles(context, *(void**)&handler)) {
				
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

		bool handles(void* context, void* handler);

	  protected:

		void* m_xContext;
		void* m_xHandler;
	};

	template <class T>
	class EventHandler : public AbstractEventHandler {
	
	  public:

		EventHandler(T* context, void (T::*handler)(const Event&)) {

			m_xContext = context;
			m_xHandler = *(void**)&handler; //Haxx cast
		}

		void handle(const Event& e) {
		
			void (T::*handler)(const Event& e) = *(void (T::**)(const Event& e))&m_xHandler; //Haxx cast
			(((T*)m_xContext)->*handler)(e);
		}
	};

	typedef std::vector<AbstractEventHandler*> HandlerList;
	HandlerList m_xHandlers[Event::EVENT_N];
};

#endif