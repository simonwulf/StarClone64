#include "MeshManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "LogManager.h"
#include <vector>
#include "TextureManager.h"

MeshManager MeshManager::m_instance;

MeshManager::MeshManager() {

	m_xMeshTable = new std::unordered_map<std::string, Mesh*>();
	Log::Writeln("MeshManager started.");
}

MeshManager::~MeshManager() {

	clearCache();
	delete m_xMeshTable;
}

Mesh* MeshManager::getMesh( std::string meshName, unsigned int loadFlags /*= 0*/ ) {

	//Log::Write("Mesh requested " + meshName + "\t");
	try {
		Mesh* mesh = getInstance().m_xMeshTable->at(meshName);

		#pragma region Logging
		/* *
		Log::Write("returned from cache", Log::COLOR_LIGHT_AQUA);

		if(mesh->isDummy())
			Log::Warn("\twarning: dummy mesh!");
		else
			Log::Writeln("");
		/* */
		#pragma endregion

		return mesh;
	}
	catch (std::out_of_range) { /* Mesh hasn't been cached/loaded */
		getInstance().loadMesh(meshName, loadFlags);
		return getInstance().getMesh(meshName, loadFlags);
	}
}

void MeshManager::loadMesh( std::string meshName, unsigned int loadFlags /*= 0*/ ) {

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(meshName, loadFlags | 
		aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

	if(scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Log::Err("Failed to load mesh " + meshName);
		m_xMeshTable->insert(std::make_pair<std::string, Mesh*>(meshName, new Mesh())); //Dummy mesh
		return;
	}

	std::vector<SubMesh*>* meshes = new std::vector<SubMesh*>();
	loadMesh_RecursiveProcess(scene->mRootNode, scene, *meshes);
	Mesh* mesh = new Mesh();
	mesh->m_xMeshes = meshes;
	m_xMeshTable->insert(std::make_pair<std::string, Mesh*>(meshName, mesh)); //Dummy mesh

}

void MeshManager::loadMesh_RecursiveProcess( aiNode* node, const aiScene* scene, std::vector<SubMesh*>& meshes ) {

	for(unsigned int i = 0; i < node->mNumMeshes; i++) {

		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene, meshes);
	}

	//Recursion
	for(unsigned int i = 0; i < node->mNumChildren; i++) {

		loadMesh_RecursiveProcess(node->mChildren[i], scene, meshes);
	}
}

void MeshManager::processMesh( aiMesh* mesh, const aiScene* scene, std::vector<SubMesh*>& meshes ) {

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	aiColor4D col;
	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

	aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &col);
	glm::vec3 defaultColor(col.r, col.g, col.b);

	for(unsigned int i = 0; i < mesh->mNumVertices; i++) {

		Vertex tmpVertex;
		glm::vec3 tmpVec;

		//Vertices
		tmpVec.x = mesh->mVertices[i].x;
		tmpVec.y = mesh->mVertices[i].y;
		tmpVec.z = mesh->mVertices[i].z;
		tmpVertex.position = tmpVec;

		//Normals
		tmpVec.x = mesh->mNormals[i].x;
		tmpVec.y = mesh->mNormals[i].y;
		tmpVec.z = mesh->mNormals[i].z;
		tmpVertex.normal = tmpVec;

		//Tangents
		if(mesh->mTangents != nullptr) {

			tmpVec.x = mesh->mTangents[i].x;
			tmpVec.y = mesh->mTangents[i].y;
			tmpVec.z = mesh->mTangents[i].z;
		} else {

			tmpVec.x = 1.0f;
			tmpVec.y = 0.0f;
			tmpVec.z = 0.0f;
		}
		tmpVertex.tangent = tmpVec;

		//Color
		if(mesh->mColors[0] != nullptr) {

			tmpVec.x = mesh->mColors[0][i].r;
			tmpVec.y = mesh->mColors[0][i].g;
			tmpVec.z = mesh->mColors[0][i].b;
		} else {
			tmpVec = defaultColor;
		}
		tmpVertex.color = tmpVec;

		//UV
		if(mesh->mTextureCoords[0] != nullptr) {

			tmpVec.x = mesh->mTextureCoords[0][i].x;
			tmpVec.y = mesh->mTextureCoords[0][i].y;
			tmpVec.z = mesh->mTextureCoords[0][i].z;
		} else {
			tmpVec.x = 0.0f;
			tmpVec.y = 0.0f;
			tmpVec.z = 0.0f;
		}
		tmpVertex.uv = glm::vec2(tmpVec);

		vertices.push_back(tmpVertex);
	}

	for(unsigned int i = 0; i < mesh->mNumFaces; i++) {

		aiFace face = mesh->mFaces[i];

		for(unsigned int j = 0; j < face.mNumIndices; j++) {

			indices.push_back(face.mIndices[j]);
		}
	}
	unsigned int num = mat->GetTextureCount(aiTextureType_DIFFUSE);
	for(unsigned int i = 0; i < num; i++) {

		aiString str;
		mat->GetTexture(aiTextureType_DIFFUSE, i, &str);
		Texture* texture = TextureManager::getTexture2D(str.C_Str(), TEX_TYPE_DIFFUSE);

		textures.push_back(*texture);
	}

	meshes.push_back(new SubMesh(&vertices, &indices, &textures));
}

void MeshManager::clearCache() {
	for(std::unordered_map<std::string, Mesh*>::iterator it = getInstance().m_xMeshTable->begin(); it != getInstance().m_xMeshTable->end(); ++it) {
	
		Mesh* mesh = it->second;

		delete mesh;
	}

	getInstance().m_xMeshTable->clear();
	Log::Writeln("MeshManager cache cleared");
}
