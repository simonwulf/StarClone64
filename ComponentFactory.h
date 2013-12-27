#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "stdafx.h"

#include <vector>

#include "Component.h"

class ComponentFactory {

  public:

	typedef std::vector<Component*> ComponentList;

	template <class T>
	Component* create() {
	
		Component* c = new T();

		m_xComponents[c->getType()].push_back(c);

		return c;
	}

	void destroy(Component* component);
	//void update(Component::Type type, float delta, float elapsedTime);

	const ComponentList* getList(Component::Type type);

	static ComponentFactory* instance();

  private:

	ComponentFactory();

	static ComponentFactory s_xInstance;

	ComponentList m_xComponents[Component::TYPE_N];
};

#endif