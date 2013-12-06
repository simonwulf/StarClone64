#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
#include <glext.h>
#include <wglext.h>
#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>

#include "Shader.h"

class vec3
{
public:
	float x,y,z;

	vec3(): x(0.0f), y(0.0f), z(0.0f){}
};
int main(int argc, const char* argv[])
{
	GLFWwindow* window;

	glewExperimental = true;

	if(!glfwInit())
		return -1;

	glfwWindowHint(GLFW_RESIZABLE, 0);
	window = glfwCreateWindow(1280, 720, "OpenGL Window", NULL/*glfwGetPrimaryMonitor()*/, NULL);
	glfwMakeContextCurrent(window);

	int MajorVersion;
	int MinorVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);

	std::cout << "OpenGL v" << MajorVersion << "." << MinorVersion << "\n";

	if(glewInit() == GLEW_OK)
		std::cout << "glew works\n";

	std::cout << "GLEW version " << glewGetString(GLEW_VERSION) << "\n";

	/* Test assimp bindings */
	Assimp::Importer importer;
	const aiScene* mesh = importer.ReadFile("test/mesh_test/grass.obj", 0);
	if(mesh)
		std::cout << "assimp works\n";



	/* Test loop */
	GLuint VBO;
	glGenBuffers(1, &VBO);
	vec3 verts[3];
	verts[0].x = -1.0f;
	verts[0].y = -1.0f;
	verts[0].z =  0.0f;
	verts[1].x =  1.0f;
	verts[1].y = -1.0f;
	verts[1].z =  0.0f;
	verts[2].x =  0.0f;
	verts[2].y =  0.1f;
	verts[2].z =  0.0f;
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3), verts, GL_STATIC_DRAW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	ShaderProgram shaderProgram("bar.vert", "foo.frag");

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram.glID());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);

		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}