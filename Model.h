#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Material.h"

/**
 * A Model is a grouping of a Mesh and a Material
 **/

class Model {

  public:

	Model();
	Model(std::string filepath, unsigned int loadFlags = 0); //Load a model from an .obj file
	~Model();

	std::string getPath() const;

	Mesh* getMeshes();
	//const Material* getMaterials() const;

	unsigned int numMeshes() const;
	//unsigned int numMaterials() const;

  private:

	static const char* s_sBasePath;
	std::string m_sFilepath;

	Mesh* m_xMeshes;
	Material* m_xMaterials;

	unsigned int m_iNumMeshes;
	unsigned int m_iNumMaterials;

	static std::allocator<Mesh> s_xMeshAllocator;
	static std::allocator<Material> s_xMaterialAllocator;
};

#endif