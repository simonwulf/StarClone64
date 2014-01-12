#include "ShaderProgram.h"

//===============//
// ShaderProgram //
//===============//
ShaderProgram::ShaderProgram(GLuint id, int options) {

	m_iGLShaderProgramID = id;
	m_iShaderFlags = options;
}

ShaderProgram::~ShaderProgram() {

}

GLuint ShaderProgram::glID() const {

	return m_iGLShaderProgramID;
}

GLint ShaderProgram::getUniformLocation(const char* name) {

	unimap::const_iterator found = m_iUniformLocations.find(name);
	
	if (found == m_iUniformLocations.end()) {
	
		GLint location = glGetUniformLocation(m_iGLShaderProgramID, name);

		m_iUniformLocations[name] = location;
		return location;
	
	} else {

		return found->second;
	}
}

//==================//
// Uniform Wrappers //
//==================//
void ShaderProgram::uniform1f(const char* name, GLfloat v0) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform1f(m_iGLShaderProgramID, location, v0);
}

void ShaderProgram::uniform2f(const char* name, GLfloat v0, GLfloat v1) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform2f(m_iGLShaderProgramID, location, v0, v1);
}

void ShaderProgram::uniform3f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform3f(m_iGLShaderProgramID, location, v0, v1, v2);
}

void ShaderProgram::uniform4f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform4f(m_iGLShaderProgramID, location, v0, v1, v2, v3);
}

void ShaderProgram::uniform1i(const char* name, GLint v0) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform1i(m_iGLShaderProgramID, location, v0);
}

void ShaderProgram::uniform2i(const char* name, GLint v0, GLint v1) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform2i(m_iGLShaderProgramID, location, v0, v1);
}

void ShaderProgram::uniform3i(const char* name, GLint v0, GLint v1, GLint v2) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform3i(m_iGLShaderProgramID, location, v0, v1, v2);
}

void ShaderProgram::uniform4i(const char* name, GLint v0, GLint v1, GLint v2, GLint v3) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform4i(m_iGLShaderProgramID, location, v0, v1, v2, v3);
}

void ShaderProgram::uniform1ui(const char* name, GLuint v0) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform1ui(m_iGLShaderProgramID, location, v0);
}

void ShaderProgram::uniform2ui(const char* name, GLuint v0, GLuint v1) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform2ui(m_iGLShaderProgramID, location, v0, v1);
}

void ShaderProgram::uniform3ui(const char* name, GLuint v0, GLuint v1, GLuint v2) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform3ui(m_iGLShaderProgramID, location, v0, v1, v2);
}

void ShaderProgram::uniform4ui(const char* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform4ui(m_iGLShaderProgramID, location, v0, v1, v2, v3);
}

void ShaderProgram::uniform1fv(const char* name, GLsizei count, const GLfloat* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform1fv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform2fv(const char* name, GLsizei count, const GLfloat* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform2fv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform3fv(const char* name, GLsizei count, const GLfloat* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform3fv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform4fv(const char* name, GLsizei count, const GLfloat* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform4fv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform1iv(const char* name, GLsizei count, const GLint* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform1iv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform2iv(const char* name, GLsizei count, const GLint* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform2iv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform3iv(const char* name, GLsizei count, const GLint* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform3iv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform4iv(const char* name, GLsizei count, const GLint* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform4iv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform1uiv(const char* name, GLsizei count, const GLuint* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform1uiv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform2uiv(const char* name, GLsizei count, const GLuint* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform2uiv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform3uiv(const char* name, GLsizei count, const GLuint* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform3uiv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniform4uiv(const char* name, GLsizei count, const GLuint* value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniform4uiv(m_iGLShaderProgramID, location, count, value);
}

void ShaderProgram::uniformMatrix2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniformMatrix2fv(m_iGLShaderProgramID, location, count, transpose, value);
}

void ShaderProgram::uniformMatrix3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniformMatrix3fv(m_iGLShaderProgramID, location, count, transpose, value);
}

void ShaderProgram::uniformMatrix4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniformMatrix4fv(m_iGLShaderProgramID, location, count, transpose, value);
}

void ShaderProgram::uniformMatrix2x3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniformMatrix2x3fv(m_iGLShaderProgramID, location, count, transpose, value);
}

void ShaderProgram::uniformMatrix3x2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniformMatrix3x2fv(m_iGLShaderProgramID, location, count, transpose, value);
}

void ShaderProgram::uniformMatrix2x4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniformMatrix2x4fv(m_iGLShaderProgramID, location, count, transpose, value);
}

void ShaderProgram::uniformMatrix4x2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniformMatrix4x2fv(m_iGLShaderProgramID, location, count, transpose, value);
}

void ShaderProgram::uniformMatrix3x4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniformMatrix3x4fv(m_iGLShaderProgramID, location, count, transpose, value);
}

void ShaderProgram::uniformMatrix4x3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value) {

	GLint location = getUniformLocation(name);

	if (location == -1)
		return;

	glProgramUniformMatrix4x3fv(m_iGLShaderProgramID, location, count, transpose, value);
}