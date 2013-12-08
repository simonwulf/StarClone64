#include "Renderer.h"
#include "RenderComponent.h"

Renderer::Renderer(GLFWwindow* window) {

	m_xWindow = window;

	m_xDefaultShaderProgram = new ShaderProgram("default.vert", "default.frag");

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

	renderNode(scene->getRoot());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glfwSwapBuffers(m_xWindow);
}

void Renderer::renderNode(GameObject* node) {

	Mesh* mesh = node->getRenderComponent()->getMesh();

	glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBufferID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBufferID());

	//Vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	
	//Vertex colors
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*)sizeof(glm::vec3));

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
}