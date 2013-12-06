#ifndef SHADER_H
#define SHADER_H

class Shader {

  public:

	Shader();
	~Shader();

  private:

	unsigned int m_glShaderID;
};

class ShaderProgram {

  public:

	ShaderProgram();
	~ShaderProgram();

  private:

	unsigned int m_glShaderProgramID;

	Shader* m_xVertexShader;
	Shader* m_xFragmentShader;
};

#endif