#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "Scene.h"

class GameState {

  public:

	GameState();
	virtual ~GameState();

	void start();
	void update(float delta, float elapsedTime);
	void render(Renderer* renderer);

  protected:

	void addScene(Scene* scene);

  private:

	std::vector<Scene*> m_xScenes;
};

#endif