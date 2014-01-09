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

	ShaderProgram* getDefaultShader() { return m_xDefaultShaderProgram; };

  private:

	static const unsigned int DIR_LIGHT_BLOCK_SIZE = 32;
	static const unsigned int POINT_LIGHT_BLOCK_SIZE = 32;

	enum LightType {
	
		LT_DIRECTIONAL,
		LT_POINT
	};

	enum BindingPoints {
	
		BP_DIRECTIONAL_LIGHTS,
		BP_POINT_LIGHTS
	};

	GLFWwindow* m_xWindow;

	//glm::mat4 m_mWorld;
	//glm::mat4 m_mPerspective;
	//glm::mat4 m_mView;

	ShaderProgram* m_xDefaultShaderProgram;

	GLuint m_iDirLightsIndex;
	GLuint m_iPointLightsIndex;

	GLuint m_iDirLightsBuffer;
	GLuint m_iPointLightsBuffer;

	void renderNode(GameObject* node);

	void updateLights(LightType type, Scene* scene);
};

#endif