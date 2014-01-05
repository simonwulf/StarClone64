#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include "CameraComponent.h"

class Scene {

  public:

	Scene();
	~Scene();

	GameObject* getRoot();

	void add(GameObject* gameObject);

	void useCamera(CameraComponent* camera);

  private:

	GameObject* m_xRoot;

	CameraComponent* m_xCamera;

	unsigned int m_iClearFlags;
	glm::vec3 m_vAmbientLight;
};

#endif