#include "ComponentFactory.h"

#include "LogManager.h"

ComponentFactory ComponentFactory::s_xInstance;

ComponentFactory::ComponentFactory() {

}

ComponentFactory* ComponentFactory::instance() {

	return &s_xInstance;
}

void ComponentFactory::destroy(Component* component) {

	Component::Type type = component->getType();

	for (unsigned int i = 0; i < m_xComponents[type].size(); ++i) {
	
		if (m_xComponents[type][i] == component) {
		
			delete component;
			m_xComponents[type].erase(m_xComponents[type].begin() + i);
			return;
		}
	}

	Log::Warn("ComponentFactory: Trying to destroy unmanaged Component");
}

void ComponentFactory::update(Component::Type type, float delta, float elapsedTime) {

	for (unsigned int i = 0; i < m_xComponents[type].size(); ++i) {
	
		m_xComponents[type][i]->update(delta, elapsedTime);
	}
}