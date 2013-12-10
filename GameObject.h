#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

class RenderComponent;

class GameObject {

  public:

	GameObject();
	~GameObject();

	const glm::mat4& getMatrix();

	RenderComponent* getRenderComponent() const;

	unsigned int numChildren() const;
	GameObject* childAt(unsigned int index) const;

	void addChild(GameObject* child);
	void removeChild(GameObject* child);

	const glm::vec3& getPosition() const;
	const glm::vec3& getScale() const;
	const glm::quat& getRotation() const;

	void setPosition(const glm::vec3& position);
	void setScale(const glm::vec3& scale);
	void setRotation(const glm::quat& rotation);

  private:

	glm::vec3 m_vPosition;
	glm::vec3 m_vScale;
	glm::quat m_qRotation;

	glm::mat4x4 m_mMatrix;
	bool m_bUpdateMatrix;

	RenderComponent* m_xRenderComponent;

	GameObject* m_xParent;

	std::vector<GameObject*> m_xChildren;
	//std::vector<Component*> m_xComponents;

	void invalidateMatrix();
};

#endif