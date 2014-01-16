#include "Game.h"

#include "Input.h"
#include "CollisionManager.h"

/*#include "PlayScene.h"
#include "HUDScene.h"
#include "SkyScene.h"
#include "MenuGUIScene.h"
#include "Menu3DScene.h"*/

#include "MenuState.h"
#include "PlayState.h"


Game* Game::s_xInstance = nullptr;

Game::Game() {

	if (s_xInstance != nullptr)
		throw std::exception("Singleton class Game has already been instantiated");

	s_xInstance = this;

	m_fElapsedTime = 0.0f;
	m_fTimeScale = 1.0f;

	m_iState = (State)-1;
	m_xCurrentState = nullptr;
}

Game::~Game() {

	glfwTerminate();

	delete m_xRenderer;

	/*for (unsigned int i = 0; i < m_xScenes.size(); ++i) {
	
		delete m_xScenes[i];
	}*/

	if (m_xCurrentState != nullptr)
		delete m_xCurrentState;

	std::cout << "Memory allocated for GameObjects: " << GameObject::getAllocatedMemorySize() << std::endl;
	std::cout << "Memory allocated for Components: " << Component::getAllocatedMemorySize() << std::endl;

	if (GameObject::getAllocatedMemorySize() > 0) {
		
		Log::Warn("All GameObjects have not been deallocated");
	}

	if (Component::getAllocatedMemorySize() > 0) {
		
		Log::Warn("All Components have not been deallocated");
	}
}

Game* Game::instance() {

	return s_xInstance;
}

int Game::init() {

	glewExperimental = true;
	
	if (!glfwInit()) {
	
		Log::Err("Failed to initialize GLFW");
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);
	/* *
	int monitor_count;
	GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
	m_xWindow = glfwCreateWindow(1920, 1080, "OpenGL Window", monitor_count > 1 ? monitors[1] : monitors[0], nullptr);
	/* */
	m_xWindow = glfwCreateWindow(1280, 720, "OpenGL Window", nullptr, nullptr);
	glfwMakeContextCurrent(m_xWindow);

	glfwGetWindowSize(m_xWindow, &m_vWindowSize.x, &m_vWindowSize.y);

	int MajorVersion;
	int MinorVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);

	std::cout << "OpenGL v" << MajorVersion << "." << MinorVersion << std::endl;

	if(glewInit() != GLEW_OK) {

		Log::Err("Failed to initialize GLEW");
		return -1;
	}

	std::cout << "GLEW version " << glewGetString(GLEW_VERSION) << "\n";

	m_xRenderer = new Renderer(m_xWindow);
	
	/*m_xPlayScene = new PlayScene();
	m_xSkyScene = new SkyScene();
	m_xSkyScene->setVisible(true);
	m_xHUDScene = new HUDScene();
	m_xMenuGUIScene = new MenuGUIScene();
	//m_xMenu3DScene = new Menu3DScene();*/

	/*m_xScenes.push_back(m_xSkyScene);
	m_xScenes.push_back(m_xPlayScene);
	m_xScenes.push_back(m_xHUDScene);
	m_xScenes.push_back(m_xMenuGUIScene);
	//m_xScenes.push_back(m_xMenu3DScene);*/

	Input::instance()->init(m_xWindow);

	std::cout << "Memory allocated for GameObjects: " << GameObject::getAllocatedMemorySize() << std::endl;
	std::cout << "Memory allocated for Components: " << Component::getAllocatedMemorySize() << std::endl;

	_setState(MENU_STATE);

	return 0;
}

void Game::loop() {

	m_iLastTime = m_iStartTime = clock();
	m_fElapsedTime = 0.0f;
	float delta = 0.0f;

	dispatchEvent(Event(Event::GAME_START));

	while(!glfwWindowShouldClose(m_xRenderer->getWindow())) {
	
		glfwPollEvents();

		update(delta, m_fElapsedTime);
		render();

		if (m_iNextState != m_iState)
			_setState(m_iNextState);

		clock_t now = clock();
		delta = ((float)(now - m_iLastTime) / (float)CLOCKS_PER_SEC) * m_fTimeScale;
		m_fElapsedTime += delta;
		m_iLastTime = now;
	}
}

void Game::quit() {

	glfwSetWindowShouldClose(m_xWindow, true);
}

/*void Game::pause() {

	if (m_iState != PAUSE_STATE)
		setState(PAUSE_STATE);
	else
		setState(PLAY_STATE);
}*/

void Game::setState(State state) {

	m_iNextState = state;
}

void Game::_setState(State state) {

	m_iState = state;
	m_iNextState = state;

	if (m_xCurrentState != nullptr)
		delete m_xCurrentState;

	switch (state) {
	
		case MENU_STATE:
			m_xCurrentState = new MenuState();
			break;

		case PLAY_STATE:
			m_xCurrentState = new PlayState();
			break;
	}
}

Game::State Game::getState() const {

	return m_iState;
}

void Game::update(float delta, float elapsedTime) {

	Input::instance()->update();

	m_xCurrentState->update(delta, elapsedTime);

	
}

void Game::render() {

	m_xCurrentState->render(m_xRenderer);

	glfwSwapBuffers(m_xWindow);
}

Event Game::makeGameEvent(Event::Type type) {

	Event e(type);
	e.game.delta = 0.0f;
	e.game.elapsedTime = m_fElapsedTime;
	e.game.state = m_iState;

	return e;
}

const glm::ivec2& Game::getWindowSize() const {

	return m_vWindowSize;
}