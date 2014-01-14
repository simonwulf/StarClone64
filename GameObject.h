#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

//#include "ComponentFactory.h"
#include "EventDispatcher.h"

class Scene;
class Component;

class GameObject : public EventDispatcher {
	
  public:

	GameObject();
	virtual ~GameObject();

	static void* operator new(size_t size);
	static void* operator new(size_t size, void* p);
	static void operator delete(void* ptr);
	static unsigned int getAllocatedMemorySize();

	const glm::mat4& getMatrix();
	const glm::mat4& getInverseMatrix();

	glm::vec3 forward();
	glm::vec3 up();
	glm::vec3 right();

	GameObject* getParent();
	Scene* getScene();

	unsigned int numChildren() const;
	GameObject* childAt(unsigned int index) const;
	void addChild(GameObject* child);
	void removeChild(GameObject* child);

	template <class T>
	T* addComponent() {
		
		//T* component = ComponentFactory::instance()->create<T>();
		T* component = new T();

		component->m_xGameObject = this;
		m_xComponents.push_back(component);

		if (m_xScene != nullptr)
			registerWithScene(component);

		return component;
	}
	void removeComponent(Component* component);
	unsigned int numComponents() const;
	Component* getComponent(unsigned int type, unsigned int offset = 0);
	unsigned int getComponents(unsigned int type, Component* dest[]);

	glm::vec3 getPosition() const;
	glm::vec3 getWorldPosition();
	glm::vec3 getScale() const;
	glm::quat getRotation() const;

	void setPosition(glm::vec3 position);
	void setScale(glm::vec3 scale);
	void setRotation(glm::quat rotation);

	void appendPosition(glm::vec3 position);
	void appendScale(glm::vec3 scale);
	void appendRotation(glm::quat rotation);

	void lookAt(glm::vec3 globalTarget, glm::vec3 up);
	glm::vec3 localToGlobal(glm::vec3 position);
	glm::vec3 globalToLocal(glm::vec3 position);

	void setTag(std::string tag);
	std::string getTag() const;

	void destroy();

  private:

	static unsigned int s_iAllocatedMemorySize;

	glm::vec3 m_vPosition;
	glm::vec3 m_vScale;
	glm::quat m_qRotation;

	glm::mat4 m_mMatrix;
	glm::mat4 m_mInverseMatrix;
	bool m_bUpdateMatrix;
	bool m_bUpdateInverseMatrix;

	std::string m_sTag;
	bool m_bDead;

	GameObject* m_xParent;
	Scene* m_xScene;

	std::vector<GameObject*> m_xChildren;
	std::vector<Component*> m_xComponents;

	void setScene(Scene* scene);
	void registerWithScene(Component* component);

	void invalidateMatrix();

	friend class Scene;
};

#endif