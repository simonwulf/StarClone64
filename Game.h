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
#include <thread>
#include <mutex>

class Scene;

class Game : public EventDispatcher {

  public:

	enum State {
	
		MENU_STATE,
		PLAY_STATE,
		PAUSE_STATE,
		LOADING_STATE
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

	/* Helper function for other object to explicitly set rendering context owner */
	void giveRCMain();
	void giveRCLoading();

  private:

	static Game* s_xInstance;

	GLFWwindow* m_xWindow;
	Renderer* m_xRenderer;

	GameState* m_xCurrentState;
	GameState* m_xLoadingState;
	State m_iState;
	State m_iNextState;

	std::thread m_tLoadingThread;
	std::mutex m_xMutex;

	glm::ivec2 m_vWindowSize;

	clock_t m_iLastTime;
	clock_t m_iStartTime;
	float m_fElapsedTime;
	float m_fTimeScale;
	bool m_bLoading;

	void update(float delta, float elapsedTime);
	void render();

	void _setState(State state);
	/* State loading function for use by a separate thread. */
	void _setState_t();
	void threadTest();

	/* Device Context shared by Main Thread and Loading Thread */
	HDC m_xDeviceContext;
	/* Main Thread's rendering context */
	HGLRC m_xRC_MThread;
	/* Loading Thread's rendering context */
	HGLRC m_xRC_LThread;

	Event makeGameEvent(Event::Type type);
};

#endif