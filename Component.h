#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"
#include "Visitor.h"

class Component {

  public:

	enum Type {
	
		UNSPECIFIED,

		CAMERA,
		RENDER,
		
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,

		CONTROLLER,
		COLLIDER,

		CUSTOM,

		TYPE_N
	};

	Component(Type type = UNSPECIFIED);
	virtual ~Component();

	static void* operator new(size_t size);
	static void* operator new(size_t size, void* p);
	static void operator delete(void* ptr);
	static unsigned int getAllocatedMemorySize();

	virtual void accept(Visitor* visitor);

	//virtual void update(float delta, float elapsedTime);

	Type getType();
	GameObject* getGameObject();

  protected:

	GameObject* m_xGameObject;

  private:

	static unsigned int s_iAllocatedMemorySize;

	Type m_iType;

	//friend Component* GameObject::addComponent(Component* component);
	//friend void GameObject::removeComponent(Component* component);
	friend class GameObject;
};

#endif