#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include "CameraComponent.h"

class Scene {

  public:

	Scene();
	virtual ~Scene();

	GameObject* getRoot();

	void add(GameObject* gameObject);

	void useCamera(CameraComponent* camera);
	const CameraComponent* getCamera() const;

	GLuint getClearFlags() const;
	void setClearFlags(GLuint flags);

	const glm::vec3& getAmbientLight() const;
	void setAmbientLight(const glm::vec3& light);

  private:

	GameObject* m_xRoot;

	CameraComponent* m_xCamera;

	GLuint m_iClearFlags;
	glm::vec3 m_vAmbientLight;
};

#endif