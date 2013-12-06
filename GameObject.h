#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

class Component;

class GameObject {

  public:

	GameObject();
	~GameObject();

  private:

	static const unsigned int MAX_COMPONENTS = 16;

	glm::vec3 m_vPosition;
	glm::vec3 m_vScale;
	glm::quat m_xRotation;

	Component* m_xComponents[MAX_COMPONENTS];
};

#endif