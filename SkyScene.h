#ifndef SKYSCENE_H
#define SKYSCENE_H

#include "Scene.h"

class SkyScene : public Scene {

	public:
		SkyScene();

		void init(GameObject* camRef);
};

#endif