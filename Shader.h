#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "LogManager.h"

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
	
	void uniform1f(const char* name, GLfloat v0);
	void uniform2f(const char* name, GLfloat v0, GLfloat v1);
	void uniform3f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2);
	void uniform4f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

	void uniform1i(const char* name, GLint v0);
	void uniform2i(const char* name, GLint v0, GLint v1);
	void uniform3i(const char* name, GLint v0, GLint v1, GLint v2);
	void uniform4i(const char* name, GLint v0, GLint v1, GLint v2, GLint v3);

	void uniform1ui(const char* name, GLuint v0);
	void uniform2ui(const char* name, GLuint v0, GLuint v1);
	void uniform3ui(const char* name, GLuint v0, GLuint v1, GLuint v2);
	void uniform4ui(const char* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);

	void uniform1fv(const char* name, GLsizei count, const GLfloat *value);
	void uniform2fv(const char* name, GLsizei count, const GLfloat *value);
	void uniform3fv(const char* name, GLsizei count, const GLfloat *value);
	void uniform4fv(const char* name, GLsizei count, const GLfloat *value);

	void uniform1iv(const char* name, GLsizei count, const GLint *value);
	void uniform2iv(const char* name, GLsizei count, const GLint *value);
	void uniform3iv(const char* name, GLsizei count, const GLint *value);
	void uniform4iv(const char* name, GLsizei count, const GLint *value);

	void uniform1uiv(const char* name, GLsizei count, const GLuint *value);
	void uniform2uiv(const char* name, GLsizei count, const GLuint *value);
	void uniform3uiv(const char* name, GLsizei count, const GLuint *value);
	void uniform4uiv(const char* name, GLsizei count, const GLuint *value);
	
	void uniformMatrix2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void uniformMatrix3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void uniformMatrix4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void uniformMatrix2x3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void uniformMatrix3x2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void uniformMatrix2x4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void uniformMatrix4x2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void uniformMatrix3x4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);
	void uniformMatrix4x3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);

  private:

	typedef std::map<std::string, GLint> unimap;

	GLuint m_iGLShaderProgramID;

	unimap m_iUniformLocations;

	Shader* m_xVertexShader;
	Shader* m_xFragmentShader;

	GLint getUniformLocation(const char* name);
};

#endif