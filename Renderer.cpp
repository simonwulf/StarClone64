#include "Renderer.h"
#include "RenderComponent.h"

#include <sstream>

Renderer::Renderer(GLFWwindow* window) {

	m_xWindow = window;

	m_xDefaultShaderProgram = new ShaderProgram("default.vert", "default.frag");

	int width, height;
	glfwGetWindowSize(m_xWindow, &width, &height);
	m_mPerspective = glm::perspective(60.0f, (float)width/(float)height, 0.1f, 1000.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.1f, 0.0f, 0.2f, 0.0f);
}

Renderer::~Renderer() {

}

GLFWwindow* Renderer::getWindow() const {

	return m_xWindow;
}

void Renderer::render(Scene* scene) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_xDefaultShaderProgram->glID());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//Vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	
	//Vertex colors
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)sizeof(glm::vec3));

	m_xDefaultShaderProgram->uniformMatrix4fv("projection", 1, GL_FALSE, (GLfloat*)&m_mPerspective);
	m_xDefaultShaderProgram->uniformMatrix4fv("view", 1, GL_FALSE, (GLfloat*)&Camera::currentCamera->getMatrix());

	renderNode(scene->getRoot());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glfwSwapBuffers(m_xWindow);
}

void Renderer::renderNode(GameObject* node) {

	m_xDefaultShaderProgram->uniformMatrix4fv("model", 1, GL_FALSE, (GLfloat*)&node->getMatrix());

	RenderComponent* rc = (RenderComponent*)node->getComponent(Component::RENDER);
	if (rc != nullptr)
		rc->render();

	for (unsigned int i = 0; i < node->numChildren(); ++i) {
	
		renderNode(node->childAt(i));
	}
}