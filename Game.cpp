#include "Game.h"

#include "RenderComponent.h"

Game* Game::s_xInstance = nullptr;

Game::Game() {

}

Game::~Game() {

	glfwTerminate();

	delete m_xRenderer;
	delete m_xScene;

	delete m_xTestObj;
	delete m_xTestCam;
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
	m_xTestObj = new GameObject();
	m_xTestObj->addComponent(new RenderComponent());
	m_xTestObj->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
	m_xScene->getRoot()->addChild(m_xTestObj);

	m_xTestCam = new GameObject();
	m_xTestCam->addComponent(new CameraComponent());
	m_xScene->getRoot()->addChild(m_xTestCam);
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
		if (delta > 0.1f)
			delta = 0.1f;
		m_fElapsedTime += delta;
		m_iLastTime = now;
	}
}

void Game::update(float delta, float elapsedTime) {

	/*m_xTestObj->setPosition(glm::vec3(
		sinf(elapsedTime * 1.0f),
		sinf(elapsedTime * 2.0f),
		-5.0f + sinf(elapsedTime * 3.0f) * 1.0f
	));*/

	/*m_xTestObj->setPosition(glm::vec3(
		0.0f,
		0.0f,
		-1.0f * elapsedTime
	));*/
	
	/*m_xTestObj->setScale(glm::vec3(
		0.55f + sinf(elapsedTime * 2.0f) * 0.45f,
		1.0f,
		0.55f + sinf(elapsedTime * 2.0f) * 0.45f
	));*/

	/* */
	m_xTestObj->setRotation(glm::angleAxis(
		elapsedTime * 90.0f,
		glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f))
	));
	/* */

	/* *
	m_xTestCam->setRotation(glm::angleAxis(
		elapsedTime * 90.0f,
		glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))
	));
	/* */

	//m_xTestCam->setPosition(glm::vec3(1.0f, 0.0f, 0.0f) * elapsedTime);
}