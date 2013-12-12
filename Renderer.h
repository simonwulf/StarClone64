#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"
#include "Shader.h"
#include "Camera.h"

class Renderer {

  public:

	Renderer(GLFWwindow* window);
	~Renderer();

	GLFWwindow* getWindow() const;

	void render(Scene* scene);

  private:

	GLFWwindow* m_xWindow;

	glm::mat4 m_mWorld;
	glm::mat4 m_mPerspective;
	glm::mat4 m_mView;

	//std::vector<glm::mat4> m_mStack;

	ShaderProgram* m_xDefaultShaderProgram;

	void renderNode(GameObject* node);

	/*void pushMatrix();
	void popMatrix();*/
};

#endif