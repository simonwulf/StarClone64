#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <vector>

class RenderComponent;

class GameObject {

  public:

	GameObject();
	~GameObject();

	const glm::mat4x4& getMatrix() const;

	RenderComponent* getRenderComponent() const;

  private:

	glm::vec3 m_vPosition;
	glm::vec3 m_vScale;
	glm::quat m_qRotation;

	glm::mat4x4 m_mMatrix;

	RenderComponent* m_xRenderComponent;

	std::vector<GameObject*> m_xChildren;
	//std::vector<Component*> m_xComponents;
};

#endif