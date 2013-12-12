#include "MeshManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "LogManager.h"
#include <vector>
#include "TextureManager.h"

MeshManager MeshManager::m_instance;

MeshManager::MeshManager() {

	m_meshTable = new std::unordered_map<std::string, Mesh*>();
	Log::Writeln("MeshManager started.");
}

MeshManager::~MeshManager() {

	clearCache();
	delete m_meshTable;
}

Mesh* MeshManager::getMesh( std::string meshName, unsigned int loadFlags /*= 0*/ ) {

	Log::Write("Mesh requested " + meshName + "\t");
	try {
		Mesh* mesh = getInstance().m_meshTable->at(meshName);

		#pragma region Logging
		Log::Write("returned from cache", Log::COLOR_LIGHT_AQUA);

		if(mesh->isDummy())
			Log::Warn("\twarning: dummy mesh!");
		else
			Log::Writeln("");
		#pragma endregion

		return mesh;
	}
	catch (std::out_of_range) { /* Mesh hasn't been cached/loaded */
		getInstance().loadMesh(meshName, loadFlags);
		return getInstance().getMesh(meshName, loadFlags);
	}
}

void MeshManager::loadMesh( std::string meshName, unsigned int loadFlags /*= 0*/ ) {

	Log::Write("loading mesh " + meshName + "\t");

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(meshName, loadFlags);

	if(!scene) {
		Log::Err("error: couldn't load mesh!");
		Mesh* dummy = new Mesh();
		dummy->setIndexArray(0, nullptr);
		dummy->setVertexArray(0, nullptr);
		m_meshTable->insert(std::make_pair<std::string, Mesh*>(meshName, dummy));
	} else {

		/* dump that shit into that mesh and put that gfx card to use son! */
		Log::Writeln("...");
		std::vector<vertex*> tempVertexArray;
		std::vector<GLuint*> tempIndexArray;
		vertex* tempVertexBuffer;
		GLuint* tempIndexBuffer;

		const aiVector3D zeroVec(0.0f, 0.0f, 0.0f);
		/* Iterate through all meshes (elements/objects) in the file */
		for(unsigned int i = 0; i < scene->mNumMeshes; i++) {

			aiMesh* mesh = scene->mMeshes[i];

			/* Collect all vertices */
			for(unsigned int j = 0; j < mesh->mNumVertices; j++) {

				vertex* vert = new vertex();
				vert->position.x = mesh->mVertices[j].x;
				vert->position.y = mesh->mVertices[j].y;
				vert->position.z = mesh->mVertices[j].z;

				if(&mesh->mNormals[j]) {

					vert->normal.x = mesh->mNormals[j].x;
					vert->normal.y = mesh->mNormals[j].y;
					vert->normal.z = mesh->mNormals[j].z;
				}
				else {

					vert->normal.x = zeroVec.x;
					vert->normal.y = zeroVec.y;
					vert->normal.z = zeroVec.z;
				}

				if(mesh->HasTextureCoords(0)) {

					vert->texcoords.x = mesh->mTextureCoords[0]->x;
					vert->texcoords.y = mesh->mTextureCoords[0]->y;
				}
				else {

					vert->texcoords.x = zeroVec.x;
					vert->texcoords.y = zeroVec.y;
				}

				tempVertexArray.push_back(vert);
			}

			/* Collect all indices */
			for(unsigned int j = 0; j < mesh->mNumFaces; j++) {

				for(int k = 0; k < 3 /* verts per face */; k++) {

					tempIndexArray.push_back(new GLuint(mesh->mFaces[j].mIndices[k]));
				}
			}
		}

		for(unsigned int i = 0; i < scene->mNumMaterials; i++) {

			const aiMaterial* material = scene->mMaterials[i];

			if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {

				aiString path;

				if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {

					std::string fullPath = "test/mesh_test/" + std::string(path.data);
					TextureManager::getTexture2D(fullPath);
				}
			}
		}
		
		tempVertexBuffer = new vertex[tempVertexArray.size()];
		tempIndexBuffer = new GLuint[tempIndexArray.size()];

		for(unsigned int i = 0; i < tempVertexArray.size(); i++)
			tempVertexBuffer[i] = *tempVertexArray[i];
		for(unsigned int i = 0; i < tempIndexArray.size(); i++)
			tempIndexBuffer[i] = *tempIndexArray[i];

		Mesh* mesh = new Mesh();
		mesh->setVertexArray(tempVertexArray.size(), tempVertexBuffer);
		mesh->setIndexArray(tempIndexArray.size(), tempIndexBuffer);

		meshBufferIDs& bufferIDs = mesh->getBufferIDs();
		
		glGenBuffers(meshBufferIDs::length, (GLuint*)&bufferIDs);

		glBindBuffer(GL_ARRAY_BUFFER, bufferIDs.vertex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIDs.index);

		glBufferData(GL_ARRAY_BUFFER, sizeof(tempVertexBuffer[0])*tempVertexArray.size(), tempVertexBuffer, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tempIndexBuffer[0])*tempIndexArray.size(), tempIndexBuffer, GL_STATIC_DRAW);

		m_meshTable->insert(std::make_pair<std::string, Mesh*>(meshName, mesh));

		Log::Success("mesh " + meshName + " loaded!");
	}
}

void MeshManager::clearCache() {

	/* Loops the mesh table and free data held by the meshes */
	for(std::unordered_map<std::string, Mesh*>::iterator it = getInstance().m_meshTable->begin();
		it != getInstance().m_meshTable->end(); ++it) {

		//std::string meshName = it->first;
		Mesh* mesh = it->second;

		delete[] mesh->getVertexArray();
		delete[] mesh->getIndexArray();

		glDeleteBuffers(meshBufferIDs::length, (GLuint*)&mesh->getBufferIDs());
	}

	getInstance().m_meshTable->clear();
	Log::Writeln("MeshManager cache cleared");
}
