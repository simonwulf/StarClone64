#ifndef SKYSCENE_H
#define SKYSCENE_H

#include "Scene.h"

class SkyCamera;

class SkyScene : public Scene {

	public:
		SkyScene();

		SkyCamera* m_xCamera;

		void setReference(GameObject* camRef);
};

#endif