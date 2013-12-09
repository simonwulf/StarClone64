#include "Shader.h"

ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {

	if (vertexShaderPath != nullptr)
		m_xVertexShader = new Shader(vertexShaderPath, GL_VERTEX_SHADER);
	else
		m_xVertexShader = nullptr;

	if (fragmentShaderPath != nullptr)
		m_xFragmentShader = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER);
	else
		m_xFragmentShader = nullptr;

	std::cout << "Linking shader program" << std::endl;
	m_iGLShaderProgramID = glCreateProgram();
	
	if (m_xVertexShader != nullptr)
		glAttachShader(m_iGLShaderProgramID, m_xVertexShader->glID());

	if (m_xFragmentShader != nullptr)
		glAttachShader(m_iGLShaderProgramID, m_xFragmentShader->glID());

	glLinkProgram(m_iGLShaderProgramID);

	GLint result = GL_FALSE;
	int infoLength;

	glGetProgramiv(m_iGLShaderProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_iGLShaderProgramID, GL_INFO_LOG_LENGTH, &infoLength);

	if (result == GL_FALSE) {
		
		char* log = new char[infoLength];
		glGetProgramInfoLog(m_iGLShaderProgramID, infoLength, nullptr, log);
		
		std::cout << log << std::endl;

		delete [] log;
	}
}

ShaderProgram::~ShaderProgram() {

	glDeleteProgram(m_iGLShaderProgramID);
}

GLuint ShaderProgram::glID() const {

	return m_iGLShaderProgramID;
}

GLint ShaderProgram::getUniformLocation(const char* name){

	unimap::const_iterator found = m_iUniformLocations.find(name);
	
	if (found == m_iUniformLocations.end()) {
	
		GLint location = glGetUniformLocation(m_iGLShaderProgramID, name);

		if (location == -1)
			return -1;

		m_iUniformLocations[name] = location;
		return location;
	
	} else {
	
		return found->second;
	}
}

Shader::Shader(const char* shaderPath, GLushort shaderType) {

	//TODO: Caching

	m_iGLShaderID = glCreateShader(shaderType);

	std::string code;
	std::ifstream file(shaderPath, std::ios_base::in);

	if (file.is_open()) {
	
		std::string line;
		while (std::getline(file, line)) {
		
			code += "\n" + line;
		}

		file.close();
	}

	std::cout << "Compiling shader: " << shaderPath << std::endl;

	GLint result = GL_FALSE;
	int infoLength = 0;

	const char* source_ptr = code.c_str();
	glShaderSource(m_iGLShaderID, 1, &source_ptr, nullptr);
	glCompileShader(m_iGLShaderID);

	glGetShaderiv(m_iGLShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_iGLShaderID, GL_INFO_LOG_LENGTH, &infoLength);

	if (result == GL_FALSE) {
		
		char* log = new char[infoLength];
		glGetShaderInfoLog(m_iGLShaderID, infoLength, nullptr, log);

		std::cout << log << std::endl;

		delete [] log;
	}
}

Shader::~Shader() {

	glDeleteShader(m_iGLShaderID);
}

GLuint Shader::glID() const {

	return m_iGLShaderID;
}