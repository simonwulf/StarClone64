#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

class Component;

class GameObject {

  public:

	GameObject();
	~GameObject();

	static void* operator new(size_t size);
	static void operator delete(void* ptr);
	static unsigned int getAllocatedMemorySize();

	const glm::mat4& getMatrix();
	const glm::mat4& getInverseMatrix();

	void setMatrix(const glm::mat4& matrix);

	//RenderComponent* getRenderComponent() const;

	GameObject* getParent();

	unsigned int numChildren() const;
	GameObject* childAt(unsigned int index) const;
	void addChild(GameObject* child);
	void removeChild(GameObject* child);

	unsigned int numComponents() const;
	void addComponent(Component* component);
	void removeComponent(Component* component);
	Component* getComponent(unsigned int type, unsigned int offset = 0);
	unsigned int getComponents(unsigned int type, Component* dest[]);

	const glm::vec3& getPosition() const;
	const glm::vec3& getScale() const;
	const glm::quat& getRotation() const;

	void setPosition(const glm::vec3& position);
	void setScale(const glm::vec3& scale);
	void setRotation(const glm::quat& rotation);

	void appendPosition(const glm::vec3& position);
	void appendScale(const glm::vec3& scale);
	void appendRotation(const glm::quat& rotation);

  private:

	static unsigned int s_iAllocatedMemorySize;

	glm::vec3 m_vPosition;
	glm::vec3 m_vScale;
	glm::quat m_qRotation;

	glm::mat4 m_mMatrix;
	glm::mat4 m_mInverseMatrix;
	bool m_bUpdateMatrix;
	bool m_bUpdateInverseMatrix;

	GameObject* m_xParent;

	std::vector<GameObject*> m_xChildren;
	std::vector<Component*> m_xComponents;

	void invalidateMatrix();
};

#endif