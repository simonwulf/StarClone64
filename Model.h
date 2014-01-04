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

	const Mesh* getMeshes() const;
	//const Material* getMaterials() const;

	unsigned int numMeshes() const;
	//unsigned int numMaterials() const;

  private:

	Mesh* m_xMeshes;
	Material* m_xMaterials;

	unsigned int m_iNumMeshes;
	unsigned int m_iNumMaterials;

	static std::allocator<Mesh> m_sMeshAllocator;
	static std::allocator<Material> m_sMaterialAllocator;
};

#endif