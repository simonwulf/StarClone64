#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Scene.h"
#include "ShaderProgram.h"
#include "Camera.h"

enum LightType {

	LT_DIRECTIONAL,
	LT_POINT,

	LT_LEN
};

enum BindingPoints {

	BP_DIRECTIONAL_LIGHTS,
	BP_POINT_LIGHTS
};

class Renderer {

  public:

	Renderer(GLFWwindow* window);
	~Renderer();

	GLFWwindow* getWindow() const;

	void render(Scene* scene);

	GLuint getLightCount(LightType type);
	void updateLights(LightType type, Scene* scene);

  private:

	static const unsigned int DIR_LIGHT_BLOCK_SIZE = 32;
	static const unsigned int POINT_LIGHT_BLOCK_SIZE = 32;

	GLFWwindow* m_xWindow;

	GLuint m_iDirLightsIndex;
	GLuint m_iPointLightsIndex;

	GLuint m_iDirLightsBuffer;
	GLuint m_iPointLightsBuffer;

	std::vector<GLuint> m_xLightCounts;

	void renderNode(GameObject* node);
};

#endif