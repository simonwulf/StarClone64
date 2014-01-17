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
#include "LoadingState.h"
#include "ShaderManager.h"


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

	if(m_tLoadingThread.joinable()) {

		Log::Write("Waiting for loading thread to finish ");
		m_tLoadingThread.join();
		Log::Success("done");
	}

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

	/* m_xRC_MThread is deleted by glfwTerminate(). LThread has to be manually deleted. */
	wglDeleteContext(m_xRC_LThread);
}

Game* Game::instance() {

	return s_xInstance;
}

int Game::init() {

	glewExperimental = true;
	m_bLoading = false;
	
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

	m_xDeviceContext = wglGetCurrentDC();
	m_xRC_MThread = wglGetCurrentContext();
	m_xRC_LThread = wglCreateContext(m_xDeviceContext);
	wglShareLists(m_xRC_MThread, m_xRC_LThread);

// 	std::cout << "Thread test\n";
// 	std::cout << "Waiting for thread\n";
// 	m_tThread = std::thread(&Game::threadTest, this);
// 	m_tThread.join();
// 	std::cout << "Thread done\n";

	m_xRenderer = new Renderer(m_xWindow);

	Input::instance()->init(m_xWindow);

	std::cout << "Memory allocated for GameObjects: " << GameObject::getAllocatedMemorySize() << std::endl;
	std::cout << "Memory allocated for Components: " << Component::getAllocatedMemorySize() << std::endl;

	ShaderManager::instance()->compileAllSubShaders();

	m_xCurrentState = nullptr;
	m_xLoadingState = new LoadingState();
	_setState(MENU_STATE);

	return 0;
}

void Game::threadTest() {

	wglMakeCurrent(m_xDeviceContext, m_xRC_LThread);
	ShaderManager::instance()->compileAllSubShaders();
	wglMakeCurrent(m_xDeviceContext, m_xRC_MThread);
}

void Game::loop() {

	m_iLastTime = m_iStartTime = clock();
	m_fElapsedTime = 0.0f;
	float delta = 0.0f;

	dispatchEvent(Event(Event::GAME_START));

	while(!glfwWindowShouldClose(m_xRenderer->getWindow())) {


		glfwPollEvents();

		wglMakeCurrent(m_xDeviceContext, m_xRC_MThread);
		if(m_bLoading) { //Assume loading thread is active and has the rendering context.
			m_xMutex.lock();
			/* Update and render only the loading scenes; */
			m_xLoadingState->update(delta, m_fElapsedTime);
			m_xLoadingState->render(m_xRenderer);
			glfwSwapBuffers(m_xWindow);
			m_xMutex.unlock();
			wglMakeCurrent(m_xDeviceContext, m_xRC_LThread); //Give back the context;

			clock_t now = clock();
			delta = ((float)(now - m_iLastTime) / (float)CLOCKS_PER_SEC) * m_fTimeScale;
			m_fElapsedTime += delta;
			m_iLastTime = now;

			continue;
		}

		if(m_xCurrentState == nullptr) {
			continue;
		}

		update(delta, m_fElapsedTime);
		render();

		if (!m_bLoading && m_iNextState != m_iState)
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

	/*	Set main thread to render temporary loading state
		Start thread
			Delete and init the current state
			Set main thread to stop rendering temporary loading state
		Join thread
		Continue as normal
	*/

	m_bLoading = true;

	if(m_tLoadingThread.joinable()) {

		m_tLoadingThread.join(); //Wait for thread to finish
	}

	//_setState_t();
	m_tLoadingThread = std::thread(&Game::_setState_t, this);
	//m_tLoadingThread.join();
}

void Game::_setState_t() {

	m_xMutex.lock();

	wglMakeCurrent(m_xDeviceContext, m_xRC_LThread);

	GameState* currentState = m_xCurrentState;

	switch (m_iState) {

	case MENU_STATE:
		m_xCurrentState = new MenuState();
		break;

	case PLAY_STATE:
		m_xCurrentState = new PlayState();
		break;
	}

	//if (currentState != nullptr)
	//	delete currentState;

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	m_bLoading = false;

	wglMakeCurrent(m_xDeviceContext, m_xRC_MThread);

	m_xMutex.unlock();
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

void Game::giveRCMain() {

	wglMakeCurrent(m_xDeviceContext, m_xRC_MThread);
}

void Game::giveRCLoading() {

	wglMakeCurrent(m_xDeviceContext, m_xRC_LThread);
}
