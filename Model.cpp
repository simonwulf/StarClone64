#include "stdafx.h"
#include <Shlwapi.h>

#include <assimp/postprocess.h>
#include "Model.h"
#include "ShaderManager.h"
#include "LogManager.h"

std::allocator<Mesh> Model::s_xMeshAllocator;
std::allocator<Material> Model::s_xMaterialAllocator;
const char* Model::s_sBasePath = "data/models";

Model::Model(std::string filepath, unsigned int loadFlags) {

	m_sFilepath = filepath;

	char model_path[MAX_PATH];
	PathCombineA(model_path, s_sBasePath, filepath.c_str());

	Log::Write("\n--- loading model " + std::string(model_path) + "\n");
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(model_path, loadFlags | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (scene == nullptr) {

		Log::Write("--- ");
		Log::Err("failed " + std::string(importer.GetErrorString()) + "\n");
		m_xMeshes = nullptr;
		m_xMaterials = nullptr;
	
	} else {

		//Materials
		m_iNumMaterials = scene->mNumMaterials;
		m_xMaterials = s_xMaterialAllocator.allocate(m_iNumMaterials);

		//Get absolute path to the model's containing folder, for use when loading textures later
		char cwd[MAX_PATH];
		char model_folder[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, cwd);
		PathCombineA(model_folder, cwd, model_path);

		//Replace all forward slashes with backslashes to satisfy PathRemoveFileSpecA
		for (unsigned int i = 0; i < MAX_PATH && model_folder[i] != 0; ++i) {
		
			if (model_folder[i] == '/')
				model_folder[i] = '\\';
		}

		PathRemoveFileSpecA(model_folder);

		for (unsigned int i = 0; i < m_iNumMaterials; ++i) {
		
			new (m_xMaterials + i) Material();
			m_xMaterials[i].setShaderProgram(ShaderManager::instance()->getProgram(SHADER_DEFAULT));

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
		m_xMeshes = s_xMeshAllocator.allocate(m_iNumMeshes);

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

		Log::Write("--- ");
		Log::Success("success\n");
	}
}

Model::~Model() {

	if (m_xMeshes != nullptr) {

		for (unsigned int i = 0; i < m_iNumMeshes; ++i) {

			s_xMeshAllocator.destroy(m_xMeshes + i);
		}

		s_xMeshAllocator.deallocate(m_xMeshes, m_iNumMeshes);
	}

	if (m_xMaterials != nullptr) {
	
		for (unsigned int i = 0; i < m_iNumMaterials; ++i) {
		
			s_xMaterialAllocator.destroy(m_xMaterials + i);
		}

		s_xMaterialAllocator.deallocate(m_xMaterials, m_iNumMaterials);
	}
}

std::string Model::getPath() const {

	return m_sFilepath;
}

Mesh* Model::getMeshes() {

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