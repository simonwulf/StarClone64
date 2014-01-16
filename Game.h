#ifndef GAME_H
#define GAME_H

#include "stdafx.h"

#include <iostream>
#include <ctime>

#include "EventDispatcher.h"
#include "GameState.h"
#include "LogManager.h"
#include "Renderer.h"

#include "GameObject.h"

class Scene;

class Game : public EventDispatcher {

  public:

	enum State {
	
		MENU_STATE,
		PLAY_STATE,
		PAUSE_STATE
	};

	Game();
	~Game();

	int init();

	void loop();
	void quit();
	//void pause();

	State getState() const;
	void setState(State state);

	const glm::ivec2& getWindowSize() const;
	Renderer* getRenderer() { return m_xRenderer; };

	static Game* instance();

  private:

	static Game* s_xInstance;

	GLFWwindow* m_xWindow;
	Renderer* m_xRenderer;

	GameState* m_xCurrentState;
	State m_iState;
	State m_iNextState;

	glm::ivec2 m_vWindowSize;

	clock_t m_iLastTime;
	clock_t m_iStartTime;
	float m_fElapsedTime;
	float m_fTimeScale;

	void update(float delta, float elapsedTime);
	void render();

	void _setState(State state);

	Event makeGameEvent(Event::Type type);
};

#endif