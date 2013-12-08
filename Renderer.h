#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Scene.h"
#include "Shader.h"

class Renderer {

  public:

	Renderer(GLFWwindow* window);
	~Renderer();

	GLFWwindow* getWindow() const;

	void render(Scene* scene);

  private:

	GLFWwindow* m_xWindow;

	glm::mat4 m_mModel;
	glm::mat4 m_mPerspective;
	glm::mat4 m_mView;

	ShaderProgram* m_xDefaultShaderProgram;

	void renderNode(GameObject* node);
};

#endif