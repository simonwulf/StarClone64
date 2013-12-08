#ifndef COMPONENT_H
#define COMPONENT_H

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

	Type type();

  private:

	Type m_iType;
};

#endif