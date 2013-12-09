#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

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
	GLint getUniformLocation(const char* name);

  private:

	typedef std::map<std::string, GLint> unimap;

	GLuint m_iGLShaderProgramID;

	unimap m_iUniformLocations;

	Shader* m_xVertexShader;
	Shader* m_xFragmentShader;
};

#endif