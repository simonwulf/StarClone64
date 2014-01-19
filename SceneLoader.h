#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <fstream>

#include "Visitor.h"
#include "Factory.h"
#include "Component.h"

class Scene;
class GameObject;

class SceneLoader : public Visitor {

  public:

	Scene* fromFile(const char* filepath);

	void visitScene(Scene* scene);
	void visitGameObject(GameObject* gameObject);
	void visitComponent(Component* component);

	void visitPerspectiveCameraComponent(PerspectiveCameraComponent* component);
	void visitModelRenderComponent(ModelRenderComponent* component);
	void visitPointLightComponent(PointLightComponent* component);
	void visitMainMenuController(MainMenuController* component);

  private:

	std::ifstream m_xFile;
	Scene* m_xScene;
	
	GameObject* readGameObject();
	void readComponent(GameObject* gameObject);

	template <typename T>
	T read() {
	
		T data;
		m_xFile.read((char*)&data, sizeof(T));

		return data;
	}
};

#endif