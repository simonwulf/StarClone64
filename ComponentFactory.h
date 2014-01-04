#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "stdafx.h"

#include <vector>

//#include "Component.h"
class Component;

class ComponentFactory {

  public:

	~ComponentFactory();

	typedef std::vector<Component*> ComponentList;

	template <class T>
	T* create() {
	
		T* c = new T();

		m_xComponents[c->getType()].push_back(c);

		return c;
	}

	void destroy(Component* component);
	//void update(Component::Type type, float delta, float elapsedTime);

	const ComponentList* getList(unsigned int type);

	static ComponentFactory* instance();

  private:

	ComponentFactory();
	ComponentFactory(const ComponentFactory&);

	static ComponentFactory s_xInstance;

	//ComponentList m_xComponents[Component::TYPE_N];
	ComponentList* m_xComponents;
};

#endif