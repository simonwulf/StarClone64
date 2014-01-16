#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "Scene.h"

class PlayScene : public Scene {

  public:

	PlayScene();

	void resetIfNeeded();

  private:

	float m_fEndTime;
	float m_bReset;

	void update(const Event& e);
	void playerKilled(const Event& e);
};

#endif