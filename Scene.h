#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"

class Scene {

  public:

	Scene();
	~Scene();

	GameObject* getRoot() const;

  private:

	GameObject* m_xRoot;
};

#endif