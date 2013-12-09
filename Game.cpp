#include "Game.h"

Game::Game() {

}

Game::~Game() {

	glfwTerminate();
}

int Game::init() {

	glewExperimental = true;
	
	if (!glfwInit()) {
	
		Log::Err("Failed to initialize GLFW");
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);
	m_xWindow = glfwCreateWindow(1280, 720, "OpenGL Window", NULL/*glfwGetPrimaryMonitor()*/, NULL);
	glfwMakeContextCurrent(m_xWindow);

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
	m_xScene = new Scene();

	//Test purposes
	m_xScene->getRoot()->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
}

void Game::loop() {

	m_iLastTime = m_iStartTime = clock();
	m_fElapsedTime = 0.0f;
	float delta = 0.0f;

	while(!glfwWindowShouldClose(m_xRenderer->getWindow())) {
	
		glfwPollEvents();

		update(delta, m_fElapsedTime);
		m_xRenderer->render(m_xScene);

		clock_t now = clock();
		delta = (float)(now - m_iLastTime) / (float)CLOCKS_PER_SEC;
		m_fElapsedTime = (float)(now - m_iStartTime) / (float)CLOCKS_PER_SEC;
		m_iLastTime = now;
	}
}

void Game::update(float delta, float elapsedTime) {

	m_xScene->getRoot()->setPosition(glm::vec3(
		sinf(elapsedTime * 1.0f),
		sinf(elapsedTime * 2.0f),
		-5.0f
	));
	
	m_xScene->getRoot()->setScale(glm::vec3(
		0.55f + sinf(elapsedTime * 2.0f) * 0.45f,
		1.0f,
		0.55f + cosf(elapsedTime * 2.0f) * 0.45f
	));

	glm::quat rotation = glm::angleAxis(elapsedTime * 90.0f, glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)));
	m_xScene->getRoot()->setRotation(rotation);
}