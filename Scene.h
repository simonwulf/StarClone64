#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"

class Scene {

  public:

	Scene();
	~Scene();

	GameObject* getRoot() const;

	void add(GameObject* gameObject);

  private:

	GameObject* m_xRoot;
};

#endif