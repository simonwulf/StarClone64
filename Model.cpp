#include "stdafx.h"
#include <Shlwapi.h>

#include <assimp/postprocess.h>
#include "Model.h"

#include "LogManager.h"

std::allocator<Mesh> Model::m_sMeshAllocator;
std::allocator<Material> Model::m_sMaterialAllocator;

Model::Model(std::string filepath, unsigned int loadFlags) {

	Log::Write("loading model " + filepath + "\n");
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filepath, loadFlags | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (scene == nullptr) {
	
		Log::Err(importer.GetErrorString());
		m_xMeshes = nullptr;
		m_xMaterials = nullptr;
	
	} else {

		//Materials
		m_iNumMaterials = scene->mNumMaterials;
		m_xMaterials = m_sMaterialAllocator.allocate(m_iNumMaterials);

		//Get absolute path to the model's containing folder, for use when loading textures later
		char cwd[MAX_PATH];
		char model_folder[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, cwd);
		PathCombineA(model_folder, cwd, filepath.c_str());

		//Replace all forward slashes with backslashes to satisfy PathRemoveFileSpecA
		for (unsigned int i = 0; i < MAX_PATH && model_folder[i] != 0; ++i) {
		
			if (model_folder[i] == '/')
				model_folder[i] = '\\';
		}

		PathRemoveFileSpecA(model_folder);

		for (unsigned int i = 0; i < m_iNumMaterials; ++i) {
		
			new (m_xMaterials + i) Material();

			const aiMaterial* material = scene->mMaterials[i];

			for (unsigned int j = 0; j < material->GetTextureCount(aiTextureType_DIFFUSE); ++j) {
			
				aiString texture_path;
				char fixed_path[MAX_PATH];

				if (material->GetTexture(aiTextureType_DIFFUSE, j, &texture_path) == AI_SUCCESS &&
					PathCombineA(fixed_path, model_folder, texture_path.C_Str()) != nullptr) {
					
					m_xMaterials[i].addTexture(fixed_path, MATERIAL_DIFFUSE);
				}
			}

			for(unsigned int j = 0; j < material->GetTextureCount(aiTextureType_HEIGHT); ++j) {


				aiString texture_path;
				char fixed_path[MAX_PATH];

				if (material->GetTexture(aiTextureType_HEIGHT, j, &texture_path) == AI_SUCCESS &&
					PathCombineA(fixed_path, model_folder, texture_path.C_Str()) != nullptr) {

						m_xMaterials[i].addTexture(fixed_path, MATERIAL_NORMALMAP);
				}
			}

			//Todo: Material attributes
		}

		//Meshes
		m_iNumMeshes = scene->mNumMeshes;
		m_xMeshes = m_sMeshAllocator.allocate(m_iNumMeshes);

		for (unsigned int i = 0; i < m_iNumMeshes; ++i) {
		
			aiMesh* mesh = scene->mMeshes[i];

			vertex* vertices = new vertex[mesh->mNumVertices];
			GLuint* indices = new GLuint[mesh->mNumFaces * 3];

			for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {

				if (mesh->HasPositions()) {

					vertices[j].position.x = mesh->mVertices[j].x;
					vertices[j].position.y = mesh->mVertices[j].y;
					vertices[j].position.z = mesh->mVertices[j].z;
				}

				if (mesh->HasNormals()) {
				
					vertices[j].normal.x = mesh->mNormals[j].x;
					vertices[j].normal.y = mesh->mNormals[j].y;
					vertices[j].normal.z = mesh->mNormals[j].z;
				}

				if (mesh->HasTextureCoords(0)) {
				
					vertices[j].texcoords.x = mesh->mTextureCoords[0][j].x;
					vertices[j].texcoords.y = mesh->mTextureCoords[0][j].y;
				}

				if(mesh->HasTangentsAndBitangents()) {

					vertices[j].tangent.x = mesh->mTangents[j].x;
					vertices[j].tangent.y = mesh->mTangents[j].y;
					vertices[j].tangent.z = mesh->mTangents[j].z;
				}
			}

			for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
			
				indices[j*3+0] = mesh->mFaces[j].mIndices[0];
				indices[j*3+1] = mesh->mFaces[j].mIndices[1];
				indices[j*3+2] = mesh->mFaces[j].mIndices[2];
			}

			new (m_xMeshes + i) Mesh(mesh->mNumVertices, vertices, mesh->mNumFaces*3, indices, &m_xMaterials[mesh->mMaterialIndex]);

			delete [] vertices;
			delete [] indices;
		}

		Log::Success("mesh " + filepath + " loaded!");
	}
}

Model::~Model() {

	if (m_xMeshes != nullptr) {
	
		//delete [] m_xMesh->getVertexArray();
		//delete [] m_xMesh->getIndexArray();

		for (unsigned int i = 0; i < m_iNumMeshes; ++i) {

			m_sMeshAllocator.destroy(m_xMeshes + i);
		}

		m_sMeshAllocator.deallocate(m_xMeshes, m_iNumMeshes);
	}

	if (m_xMaterials != nullptr) {
	
		for (unsigned int i = 0; i < m_iNumMaterials; ++i) {
		
			m_sMaterialAllocator.destroy(m_xMaterials + i);
		}

		m_sMaterialAllocator.deallocate(m_xMaterials, m_iNumMaterials);
	}
}

const Mesh* Model::getMeshes() const {

	return m_xMeshes;
}

/*const Material* Model::getMaterials() const {

	return m_xMaterials;
}*/

unsigned int Model::numMeshes() const {

	return m_iNumMeshes;
}

/*unsigned int Model::numMaterials() const {

	return m_iNumMaterials;
}*/