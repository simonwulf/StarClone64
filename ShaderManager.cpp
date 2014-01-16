#include "ShaderManager.h"
#include "LogManager.h"
#include "Renderer.h"
#include <Shlwapi.h>
#include "Material.h"

ShaderManager ShaderManager::m_sInstance;

ShaderManager* ShaderManager::instance() {

	return &m_sInstance;
}

ShaderManager::ShaderManager() {

	m_sShaderBasePath = "data/shaders";

	m_xShaderFileNames[SHADER_BASE]						= "base";
	m_xShaderFileNames[SHADER_LIGHTING_DIFFUSE]			= "lighting_diffuse";
	m_xShaderFileNames[SHADER_LIGHTING_UNLIT]			= "lighting_unlit";
	m_xShaderFileNames[SHADER_NORMAL_MAP]				= "normal_map";
	m_xShaderFileNames[SHADER_ALPHA_MASK]				= "alpha_mask";
	m_xShaderFileNames[SHADER_ALPHA_BLENDING_ADDITIVE]	= "blend_alpha_additive";
}

ShaderManager::~ShaderManager() {

	clearCache();
}

void ShaderManager::clearCache() {

	auto it_program = m_xProgramCache.begin();
	for(; it_program != m_xProgramCache.end(); ++it_program) {

		glDeleteProgram(it_program->second->glID());
		delete it_program->second;
	}
	
	m_xProgramCache.clear();

	auto it_shader = m_xShaderCache.begin();
	for(; it_shader != m_xShaderCache.end(); ++it_shader) {

		glDeleteShader(it_shader->second->vertexShader);
		glDeleteShader(it_shader->second->fragmentShader);
		glDeleteShader(it_shader->second->geometryShader);
		delete it_shader->second;
	}

	m_xShaderCache.clear();

	auto it_base = m_xBaseCache.begin();
	for(; it_base != m_xBaseCache.end(); ++it_base) {

		glDeleteShader(it_base->second->vertexShader);
		glDeleteShader(it_base->second->fragmentShader);
		glDeleteShader(it_base->second->geometryShader);
		delete it_base->second;
	}

	m_xBaseCache.clear();
}

ShaderProgram* ShaderManager::getProgram( int options ) {

	auto it = m_xProgramCache.find(options);

	if(it != m_xProgramCache.end()) {

		return it->second;
	} else {

		return buildProgram(options);
	}
}

CompleteShader* ShaderManager::getCompleteShader( SubShaders type ) {

	auto it = m_xShaderCache.find(type);

	if(it != m_xShaderCache.end()) {

		return it->second;
	} else {

		return buildCompleteShader(type);
	}
}

void ShaderManager::compileAllSubShaders() {

	int bit = 0x1;

	while(bit < SUBSHADERS_END) {

		buildCompleteShader((SubShaders)bit);
		bit = bit << 1;
	}
}

ShaderProgram* ShaderManager::buildProgram( int options ) {

	std::vector<CompleteShader*> shaders;

	//Calculate which shaders to attach to the program.
	//Order is arbitrary, but SHADER_BASE needs to be aware 
	//of the other SubShaders applied and has to be rebuilt 
	//for every material.

	if(options & SHADER_NORMAL_MAP) shaders.push_back( getCompleteShader(SHADER_NORMAL_MAP) );
	if(options & SHADER_ALPHA_MASK) shaders.push_back( getCompleteShader(SHADER_ALPHA_MASK) );
	if(options & SHADER_ALPHA_BLENDING_ADDITIVE) shaders.push_back( getCompleteShader(SHADER_ALPHA_BLENDING_ADDITIVE) );

	//Lighting probably goes (almost) last
	//Most often only a single lighting technique is used
	if(options & SHADER_LIGHTING_UNLIT) shaders.push_back( getCompleteShader(SHADER_LIGHTING_UNLIT) );
	else if(options & SHADER_LIGHTING_DIFFUSE) shaders.push_back( getCompleteShader(SHADER_LIGHTING_DIFFUSE) );


	shaders.push_back( getBaseShader(options) );

	GLuint program = glCreateProgram();

	for(unsigned int i = 0; i < shaders.size(); ++i) {

		if(shaders[i]->vertexShader != SHADER_ERR_ID) glAttachShader(program, shaders[i]->vertexShader);
		if(shaders[i]->geometryShader != SHADER_ERR_ID) glAttachShader(program, shaders[i]->geometryShader);
		if(shaders[i]->fragmentShader != SHADER_ERR_ID) glAttachShader(program, shaders[i]->fragmentShader);
	}

	Log::Write("Linking Shader Program ");
	glLinkProgram(program);

	GLint result = GL_FALSE;
	int infoLen;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

	if(result == GL_FALSE) {

		char* errLog = new char[infoLen];
		glGetProgramInfoLog(program, infoLen, nullptr, errLog);

		Log::Err("error");
		Log::Err(errLog);

		delete[] errLog;
	} else {

		ShaderProgram* shaderProgram = new ShaderProgram(program, options);
		glUniformBlockBinding(shaderProgram->glID(), glGetUniformBlockIndex(shaderProgram->glID(), "DirectionalLights"), BP_DIRECTIONAL_LIGHTS);
		glUniformBlockBinding(shaderProgram->glID(), glGetUniformBlockIndex(shaderProgram->glID(), "PointLights"), BP_POINT_LIGHTS);
		shaderProgram->uniform1i("diffuse", MATERIAL_DIFFUSE);
		shaderProgram->uniform1i("normalmap", MATERIAL_NORMALMAP);
		m_xProgramCache[options] = shaderProgram;
		Log::Success("success");
		return shaderProgram;
	}

	return nullptr;
}

CompleteShader* ShaderManager::buildCompleteShader( SubShaders type ) {

	if(type == SHADER_BASE) //BASE needs specific options
		return nullptr;

	auto shaderName = m_xShaderFileNames.find(type);

	if(shaderName == m_xShaderFileNames.end()) //A source file for the given SubShader operation has not been set
		return nullptr;

	char filePath[MAX_PATH];

	PathCombineA(filePath, m_sShaderBasePath.c_str(), shaderName->second.c_str());

	GLuint vert = SHADER_ERR_ID;
	GLuint geom = SHADER_ERR_ID;
	GLuint frag = SHADER_ERR_ID;

	std::string vertFile = std::string(filePath) + ".vert";
	std::string geomFile = std::string(filePath) + ".geom";
	std::string fragFile = std::string(filePath) + ".frag";

	bool vertExists = (bool)(std::ifstream(vertFile).is_open());
	bool geomExists = (bool)(std::ifstream(geomFile).is_open());
	bool fragExists = (bool)(std::ifstream(fragFile).is_open());

	std::stringstream ss;
	ss << "Building shader type " << type << " ";
	Log::Write(ss.str());

	Log::Write("vertex ", (vertExists) ? Log::COLOR_LIGHT_GREEN : Log::COLOR_GRAY);
	Log::Write("geometry ", (geomExists) ? Log::COLOR_LIGHT_GREEN : Log::COLOR_GRAY);
	Log::Write("fragment ", (fragExists) ? Log::COLOR_LIGHT_GREEN : Log::COLOR_GRAY);
	Log::Writeln("");

	if( vertExists ) vert = buildSingleShader(vertFile.c_str(), GL_VERTEX_SHADER, type);
	if( geomExists ) geom = buildSingleShader(geomFile.c_str(), GL_GEOMETRY_SHADER, type);
	if( fragExists ) frag = buildSingleShader(fragFile.c_str(), GL_FRAGMENT_SHADER, type);

	CompleteShader* outShader = new CompleteShader;
	outShader->vertexShader = vert;
	outShader->geometryShader = geom;
	outShader->fragmentShader = frag;

	m_xShaderCache[type] = outShader;
	return outShader;
}

GLuint ShaderManager::buildSingleShader( std::string filePath, GLenum glType, SubShaders type, const char* defines ) {

	GLuint shader = glCreateShader(glType);
	
	std::string sourceCode;
	std::ifstream shaderFile(filePath, std::ios_base::in);
	std::string versionLine = "#version 420";
	if(shaderFile.is_open()) {

		std::string line;
		while(std::getline(shaderFile, line)) {

			if(line.substr(0, 9) == "#version ") {
				versionLine = line + "\n";
				continue;
			}

			sourceCode += "\n" + line;
		}

		shaderFile.close();

		char buf_fname[MAX_PATH];
		char buf_ext[MAX_PATH];
		_splitpath_s(filePath.c_str(), nullptr, 0, nullptr, 0, buf_fname, MAX_PATH, buf_ext, MAX_PATH);
		std::stringstream ss;
		ss << buf_fname << buf_ext << " ";
		Log::Write("Compiling shader: " + ss.str());

		GLint result = GL_FALSE;
		int infoLen = 0;
		const char* sourceCode_ptr = sourceCode.c_str();

		const char* buf[3] = { versionLine.c_str(), defines, sourceCode_ptr };
		glShaderSource(shader, 3, buf, nullptr);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if(result == GL_FALSE) {

			char* errLog = new char[infoLen];
			glGetShaderInfoLog(shader, infoLen, nullptr, errLog);

			Log::Err("error");
			Log::Err(errLog);
			delete [] errLog;

			return SHADER_ERR_ID;
		} else {

			Log::Success("success");
			return shader;
		}

	} else {

		Log::Err("Couldn't open shader file: " + filePath);
	}

	return SHADER_ERR_ID;
}

CompleteShader* ShaderManager::getBaseShader( int options ) {

	auto it = m_xBaseCache.find(options);

	if(it != m_xBaseCache.end()) {

		return it->second;
	} else {

		return buildBaseShader(options);
	}
}

CompleteShader* ShaderManager::buildBaseShader( int options ) {

	auto shaderName = m_xShaderFileNames.find(SHADER_BASE);

	if(shaderName == m_xShaderFileNames.end()) //Ouch, base holds the main() so the shader program will fail.
		return nullptr;

	char filePath[MAX_PATH];

	PathCombineA(filePath, m_sShaderBasePath.c_str(), shaderName->second.c_str());

	GLuint vert = SHADER_ERR_ID;
	GLuint geom = SHADER_ERR_ID;
	GLuint frag = SHADER_ERR_ID;

	std::string vertFile = std::string(filePath) + ".vert";
	std::string geomFile = std::string(filePath) + ".geom";
	std::string fragFile = std::string(filePath) + ".frag";

	bool vertExists = (bool)(std::ifstream(vertFile).is_open());
	bool geomExists = (bool)(std::ifstream(geomFile).is_open());
	bool fragExists = (bool)(std::ifstream(fragFile).is_open());

	std::stringstream ss;
	ss << "Building base shader (0x" << std::hex << options << std::dec << ") ";
	Log::Write(ss.str());

	Log::Write("vertex ", (vertExists) ? Log::COLOR_LIGHT_GREEN : Log::COLOR_GRAY);
	Log::Write("geometry ", (geomExists) ? Log::COLOR_LIGHT_GREEN : Log::COLOR_GRAY);
	Log::Write("fragment ", (fragExists) ? Log::COLOR_LIGHT_GREEN : Log::COLOR_GRAY);
	Log::Writeln("");

	/* Add defines per shader type */
	std::stringstream macroDefines;

	if(options & SHADER_LIGHTING_DIFFUSE)			macroDefines << "#define SHADER_LIGHTING_DIFFUSE\n";
	if(options & SHADER_LIGHTING_UNLIT)				macroDefines << "#define SHADER_LIGHTING_UNLIT\n";
	if(options & SHADER_NORMAL_MAP)					macroDefines << "#define SHADER_NORMAL_MAP\n";
	if(options & SHADER_ALPHA_MASK)					macroDefines << "#define SHADER_ALPHA_MASK\n";
	if(options & SHADER_ALPHA_BLENDING_ADDITIVE)	macroDefines << "#define SHADER_ALPHA_BLENDING_ADDITIVE\n";
	
	macroDefines << "\0";
	std::string defines_str = macroDefines.str();
	const char* defines = defines_str.c_str();

	if( vertExists ) vert = buildSingleShader(vertFile.c_str(), GL_VERTEX_SHADER, SHADER_BASE, defines);
	if( geomExists ) geom = buildSingleShader(geomFile.c_str(), GL_GEOMETRY_SHADER, SHADER_BASE, defines);
	if( fragExists ) frag = buildSingleShader(fragFile.c_str(), GL_FRAGMENT_SHADER, SHADER_BASE, defines);

	CompleteShader* outShader = new CompleteShader;
	outShader->vertexShader = vert;
	outShader->geometryShader = geom;
	outShader->fragmentShader = frag;

	m_xBaseCache[options] = outShader;
	return outShader;
}
