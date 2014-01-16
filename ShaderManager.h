#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <GL\glew.h>
#include "ShaderProgram.h"
#include <unordered_map>

/* 
	Adding a new SubShader type? Edit:
		enum SubShaders					- add new shader type (order is trivial, values are never directly referenced or tied to a shader type)
		ShaderManager()					- set shader filename
		BuildProgram(int options)		- check for the correct flag and push it to the program
		BuildBaseShader(int options)	- set the correct macro defines for base.vert/.geom/.frag
		base.vert/.geom/.frag			- check for macro defines and call your new shader functions
*/
enum SubShaders {

	SHADER_BASE						= 0x00,		//Base for all shader connectivity. Will by default render unlit diffuse
	
	SHADER_LIGHTING_DIFFUSE			= 0x01,		//Standard per-pixel lighting
	SHADER_LIGHTING_UNLIT			= 0x02,		//Unlit is implied without specifying a lighting technique
	
	SHADER_NORMAL_MAP				= 0x04,		//Useless with Unlit
	SHADER_ALPHA_MASK				= 0x08,		//Fragments with alpha == 0 are discarded
	SHADER_ALPHA_BLENDING_ADDITIVE	= 0x10,		//Read before rendering; sets GL_BLEND and blend functions

	SUBSHADERS_END
};

static int SHADER_DEFAULT = SHADER_BASE | SHADER_LIGHTING_DIFFUSE;
static int SHADER_GUI = SHADER_BASE | SHADER_LIGHTING_UNLIT | SHADER_ALPHA_MASK;

struct CompleteShader {
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint geometryShader;
};

#define SHADER_ERR_ID UINT_MAX

class ShaderManager {

	public:

		~ShaderManager();

		static ShaderManager* instance();
		void clearCache();

		ShaderProgram* getProgram(int options);
		CompleteShader* getCompleteShader(SubShaders type);

		void compileAllSubShaders();

	private:

		ShaderManager();
		ShaderManager(const ShaderManager&);
		void operator=(const ShaderManager&);

		ShaderProgram* buildProgram(int options);
		CompleteShader* buildCompleteShader(SubShaders type);
		GLuint buildSingleShader(std::string filePath, GLenum glType, SubShaders type, const char* defines = "");
		
		CompleteShader* getBaseShader(int options);
		CompleteShader* buildBaseShader(int options);

		static ShaderManager m_sInstance;
		std::string m_sShaderBasePath;

		std::unordered_map<int, CompleteShader*> m_xShaderCache; //int = one 'SubShaders'
		std::unordered_map<int, std::string> m_xShaderFileNames; //int = one 'SubShaders'
		std::unordered_map<int, ShaderProgram*> m_xProgramCache; //int = OR'd 'SubShaders'
		std::unordered_map<int, CompleteShader*> m_xBaseCache;	 //int = OR'd 'SubShaders'
};

#endif