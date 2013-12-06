#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

int main(int argc, const char* argv[])
{
	GLFWwindow* window;

	glewExperimental = true;

	if(!glfwInit())
		return -1;

	glfwWindowHint(GLFW_RESIZABLE, 0);
	window = glfwCreateWindow(1280, 720, "OpenGL Window", NULL/*glfwGetPrimaryMonitor()*/, NULL);
	glfwMakeContextCurrent(window);

	glewInit();

	std::cout << "GLEW version " << glewGetString(GLEW_VERSION) << "\n";

	/* Test loop */
	while(!glfwWindowShouldClose(window))
	{
		

		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}