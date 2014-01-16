#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <gl\glew.h>

#include "EventDispatcher.h"
#include "Factory.h"
#include "GameObject.h"
#include "Component.h"
#include "LogManager.h"
#include "Raycast.h"

class CameraComponent;

class Scene : public EventDispatcher {

  public:

	Scene();
	virtual ~Scene();

	void update(float delta, float elapsedTime);
	void lateUpdate(float delta, float elapsedTime);

	template <class T>
	T* make(const std::string& type) {
	
		T* object = m_xGameObjectFactory.create<T>(type);
		if (object == nullptr) {
		
			Log::Err("Error making GameObject");
			return nullptr;
		}
		m_xGameObjects.push_back(object);
		m_xRoot->addChild(object);

		return object;
	}

	GameObject* make(const std::string& type);
	void removeDead();

	void registerComponent(Component* component);
	void removeComponent(Component* component);

	void useCamera(CameraComponent* camera);
	CameraComponent* getCamera();

	GLuint getClearFlags() const;
	void setClearFlags(GLuint flags);

	const glm::vec3& getAmbientLight() const;
	void setAmbientLight(const glm::vec3& light);

	typedef std::vector<Component*> ComponentList;
	ComponentList* getComponents(Component::Type type);

	RaycastResult raycast(Ray ray);

	void setActive(bool active);
	bool isActive() const;

  protected:

	Factory<GameObject, std::string> m_xGameObjectFactory;

	void clear();

  private:

	std::vector<GameObject*> m_xGameObjects;
	GameObject* m_xRoot;

	ComponentList m_xComponents[Component::TYPE_N];

	CameraComponent* m_xCamera;

	GLuint m_iClearFlags;
	glm::vec3 m_vAmbientLight;
	bool m_bActive;
	bool m_bVisible;

	void removeDead_r(GameObject* node);

	void inputHandler(const Event& e);

	friend class Renderer;
};

#endif