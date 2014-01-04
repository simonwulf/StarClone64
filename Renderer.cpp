#include "Renderer.h"
#include "RenderComponent.h"
#include "DirectionalLightComponent.h"
#include "ComponentFactory.h"

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

	//Generate light buffers
	glGenBuffers(2, &m_iDirLightsBuffer);

	//Bind directional lights buffer to default shader program
	m_iDirLightsIndex = glGetUniformBlockIndex(m_xDefaultShaderProgram->glID(), "DirectionalLights");
	glUniformBlockBinding(m_xDefaultShaderProgram->glID(), m_iDirLightsIndex, BP_DIRECTIONAL_LIGHTS);
	glBindBufferBase(GL_UNIFORM_BUFFER, BP_DIRECTIONAL_LIGHTS, m_iDirLightsBuffer);

	//Bind point lights buffer to default shader program
	m_iPointLightsIndex = glGetUniformBlockIndex(m_xDefaultShaderProgram->glID(), "PointLights");
	glUniformBlockBinding(m_xDefaultShaderProgram->glID(), m_iPointLightsIndex, BP_POINT_LIGHTS);
	glBindBufferBase(GL_UNIFORM_BUFFER, BP_POINT_LIGHTS, m_iPointLightsBuffer);
}

Renderer::~Renderer() {

}

GLFWwindow* Renderer::getWindow() const {

	return m_xWindow;
}

void Renderer::render(Scene* scene) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_xDefaultShaderProgram->glID());

	m_xDefaultShaderProgram->uniformMatrix4fv("projection", 1, GL_FALSE, (GLfloat*)&m_mPerspective);
	m_xDefaultShaderProgram->uniformMatrix4fv("view", 1, GL_FALSE, (GLfloat*)&Camera::currentCamera->getMatrix());
	m_xDefaultShaderProgram->uniform3f("ambient_light", 0.5f, 0.5f, 0.5f);

	updateLights(LT_DIRECTIONAL);
	updateLights(LT_POINT);

	const ComponentFactory::ComponentList* rc_list = ComponentFactory::instance()->getList(Component::RENDER);
	for (unsigned int i = 0; i < rc_list->size(); ++i) {
	
		RenderComponent* rc = (RenderComponent*)rc_list->at(i);
		m_xDefaultShaderProgram->uniformMatrix4fv("model", 1, GL_FALSE, (GLfloat*)&rc->getGameObject()->getMatrix());
		m_xDefaultShaderProgram->uniform1i("diffuse", 0);

		if (rc != nullptr)
			rc->render();
	}

	glfwSwapBuffers(m_xWindow);
}

void Renderer::updateLights(Renderer::LightType type) {

	float* data;
	unsigned int data_size;

	Component::Type component_type;
	unsigned int block_size;
	GLuint uniform_buffer;
	const char* count_uniform;

	switch (type) {
	
		case LT_DIRECTIONAL:

			component_type = Component::DIRECTIONAL_LIGHT;
			block_size = DIR_LIGHT_BLOCK_SIZE;
			uniform_buffer = m_iDirLightsBuffer;
			count_uniform = "dir_light_count";
			break;

		case LT_POINT:

			component_type = Component::POINT_LIGHT;
			block_size = POINT_LIGHT_BLOCK_SIZE;
			uniform_buffer = m_iPointLightsBuffer;
			count_uniform = "point_light_count";
			break;

		default:
			throw std::invalid_argument("Unknown light type");
	}

	const ComponentFactory::ComponentList* light_list = ComponentFactory::instance()->getList(component_type);
	data_size = light_list->size() * block_size;
	data = new float[data_size];

	float* dst = data;
	for (unsigned int i = 0; i < light_list->size(); ++i) {
	
		((LightComponent*)light_list->at(i))->glData(dst);

		dst += block_size / sizeof(float);
	}

	glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer);
	glBufferData(GL_UNIFORM_BUFFER, data_size * sizeof(float), data, GL_DYNAMIC_DRAW);

	m_xDefaultShaderProgram->uniform1ui(count_uniform, light_list->size());
	
	delete [] data;
}