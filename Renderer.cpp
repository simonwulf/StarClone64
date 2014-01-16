#include "Renderer.h"
#include "RenderComponent.h"
#include "DirectionalLightComponent.h"
#include "ComponentFactory.h"

#include "ShaderManager.h"
#include <sstream>

Renderer::Renderer(GLFWwindow* window) {

	m_xWindow = window;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.1f, 0.0f, 0.2f, 0.0f);

	//Generate light buffers
	glGenBuffers(2, &m_iDirLightsBuffer);

	//Bind directional lights buffer to default shader program
	glBindBufferBase(GL_UNIFORM_BUFFER, BP_DIRECTIONAL_LIGHTS, m_iDirLightsBuffer);

	//Bind point lights buffer to default shader program
	glBindBufferBase(GL_UNIFORM_BUFFER, BP_POINT_LIGHTS, m_iPointLightsBuffer);

	m_xLightCounts.resize(LT_LEN);
}

Renderer::~Renderer() {

}

GLFWwindow* Renderer::getWindow() const {

	return m_xWindow;
}

void Renderer::render(Scene* scene) {

	glClear(scene->getClearFlags());
	//renderNode(scene->getRoot());

	const Scene::ComponentList* rc_list = scene->getComponents(Component::RENDER);
	for (unsigned int i = 0; i < rc_list->size(); ++i) {
	
		RenderComponent* rc = (RenderComponent*)rc_list->at(i);

		if (rc != nullptr && rc->getVisible()) {

			rc->render();
		}
	}
}

//Went back to recursive approach in order to support multiple scenes
/*void Renderer::renderNode(GameObject* node) {

	RenderComponent* rc = (RenderComponent*)node->getComponent(Component::RENDER);

	if (rc != nullptr) {

		rc->render();
	}

	for (unsigned int i = 0; i < node->numChildren(); ++i) {
	
		renderNode(node->childAt(i));
	}
}*/

void Renderer::updateLights(LightType type, Scene* scene) {

	float* data;
	unsigned int data_size;

	Component::Type component_type;
	unsigned int block_size;
	GLuint uniform_buffer;
	//const char* count_uniform;

	switch (type) {
	
		case LT_DIRECTIONAL:

			component_type = Component::DIRECTIONAL_LIGHT;
			block_size = DIR_LIGHT_BLOCK_SIZE;
			uniform_buffer = m_iDirLightsBuffer;
			//count_uniform = "dir_light_count";
			break;

		case LT_POINT:

			component_type = Component::POINT_LIGHT;
			block_size = POINT_LIGHT_BLOCK_SIZE;
			uniform_buffer = m_iPointLightsBuffer;
			//count_uniform = "point_light_count";
			break;

		default:
			throw std::invalid_argument("Unknown light type");
	}

	const Scene::ComponentList* light_list = scene->getComponents(component_type);
	data_size = light_list->size() * block_size;
	data = new float[data_size];

	//Unoptimized and ugly, but this will have to do for now
	//Would perhaps be better to move creation of gameobjects and components
	//into Scene and not allow moving objects between scenes. Then a scene
	//could keep lists of the components in the scene as ComponentFactory is
	//doing now.
	float* dst = data;
	unsigned int count = 0;
	for (unsigned int i = 0; i < light_list->size(); ++i) {
	
		LightComponent* light = (LightComponent*)light_list->at(i);
		if (light->getGameObject()->getScene() != scene)
			continue;

		light->glData(dst);
		++count;

		dst += block_size / sizeof(float);
	}

	glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer);
	glBufferData(GL_UNIFORM_BUFFER, data_size * sizeof(float), data, GL_DYNAMIC_DRAW);

	m_xLightCounts[type] = count;
	
	delete [] data;
}

GLuint Renderer::getLightCount( LightType type ) {

	return m_xLightCounts[type];
}
