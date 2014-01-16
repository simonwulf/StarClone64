#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "Scene.h"

class PlayScene : public Scene {

  public:

	PlayScene();

  private:

	float m_fEndTime;

	void update(const Event& e);
	void playerKilled(const Event& e);
};

#endif