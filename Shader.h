#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader {

  public:

	Shader(const char* shaderPath, GLushort shaderType);
	~Shader();

	GLuint glID() const;

  private:

	GLuint m_iGLShaderID;
};

class ShaderProgram {

  public:

	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();

	GLuint glID() const;

  private:

	GLuint m_iGLShaderProgramID;

	Shader* m_xVertexShader;
	Shader* m_xFragmentShader;
};

#endif