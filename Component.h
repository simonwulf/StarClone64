#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"

class Component {

  public:

	enum Type {
	
		CAMERA,
		RENDER,
		
		SUN,

		CONTROLLER,
		COLLIDER
	};

	Component(Type type);
	~Component();

	virtual void update(float delta, float elapsedTime);

	Type getType();
	GameObject* getGameObject();

  private:

	Type m_iType;

	GameObject* m_xGameObject;

	friend void GameObject::addComponent(Component* component);
	friend void GameObject::removeComponent(Component* component);
};

#endif