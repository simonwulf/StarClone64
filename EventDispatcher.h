#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include "Event.h"
#include "Profiler.h"

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
	
		PROFILE_START

		for (unsigned int i = 0; i < m_xHandlers[e.type].size(); ++i) {
			m_xHandlers[e.type][i]->handle(e);
		}

		PROFILE_END
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