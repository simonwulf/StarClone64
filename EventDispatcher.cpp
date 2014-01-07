#include "EventDispatcher.h"

EventDispatcher::~EventDispatcher() {

	for (unsigned int t = 0; t < Event::EVENT_N; ++t) {
		for (unsigned int i = 0; i < m_xHandlers[t].size(); ++i) {
		
			delete m_xHandlers[t][i];
		}
	}
}