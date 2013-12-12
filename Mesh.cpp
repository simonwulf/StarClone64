#include "Mesh.h"

#include "LogManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <sstream>

Mesh::Mesh() {
	
	m_xVertices = nullptr;
	m_iIndices = nullptr;

	/*
#pragma region Mesh test
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("test/mesh_test/teapot.obj", 
		aiProcess_JoinIdenticalVertices);

	if(!scene)
	{
		Log::Err("Error loading mesh: " + std::string(importer.GetErrorString()));
		system("PAUSE >NUL");
		exit(-1);
	}
	else
	{
		int totalVertices = 0;

		std::vector<vertex*> tempVertexBuffer;
		std::vector<GLuint*> tempIndexBuffer;
		for(int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];

			int numVertices = mesh->mNumVertices;

			for(int v = 0; v < mesh->mNumVertices; v++)
			{
				vertex* vert = new vertex();
				vert->position.x = mesh->mVertices[v].x;
				vert->position.y = mesh->mVertices[v].y;
				vert->position.z = mesh->mVertices[v].z;

				vert->color = glm::vec4(
					(float)(rand())/((float)(RAND_MAX))+0.2f,
					(float)(rand())/((float)(RAND_MAX))+0.2f,
					(float)(rand())/((float)(RAND_MAX))+0.2f,
					1);
				tempVertexBuffer.push_back(vert);
			}

			for(int j = 0; j < mesh->mNumFaces; j++)
			{
				const aiFace& face = mesh->mFaces[j];

				for(int k = 0; k < 3; k++)
				{
					tempIndexBuffer.push_back(new GLuint(face.mIndices[k]));
				}
			}
		}


		m_iVertexCount = tempVertexBuffer.size();
		m_iIndexCount = tempIndexBuffer.size();

		m_xVertices = new vertex[m_iVertexCount];
		m_iIndices = new GLuint[m_iIndexCount];

		for(int i = 0; i < tempVertexBuffer.size(); i++)
		{
			m_xVertices[i] = *tempVertexBuffer[i];
			std::stringstream ss;
			ss << "[" << i << "] " << 
				m_xVertices[i].position.x << ", " <<
				m_xVertices[i].position.y << ", " <<
				m_xVertices[i].position.z;

			//Log::Writeln(ss.str(), Log::COLOR_LIGHT_BLUE);
		}
		for(int i = 0; i < tempIndexBuffer.size(); i++)
		{
			m_iIndices[i] = *tempIndexBuffer[i];
		}

		void* ptr = &m_xGLBuffers;
		glGenBuffers(2, (GLuint*)&m_xGLBuffers);

		glBindBuffer(GL_ARRAY_BUFFER, m_xGLBuffers.vertex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_xGLBuffers.index);

		glBufferData(GL_ARRAY_BUFFER, sizeof(m_xVertices[0])*m_iVertexCount, m_xVertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_iIndices[0])*m_iIndexCount, m_iIndices, GL_STATIC_DRAW);

		Log::Writeln("Loaded mesh", Log::COLOR_LIGHT_GREEN);
	}
#pragma endregion Mesh test
	*/

	/*
#pragma region Pyramid test code
	m_iVertexCount = 5;
	m_xVertices = new vertex[m_iVertexCount];
	
	//Test pyramid
	m_xVertices[0].position = glm::vec3(-1.0f, -1.0f,  1.0f);
	m_xVertices[1].position = glm::vec3( 1.0f, -1.0f,  1.0f);
	m_xVertices[2].position = glm::vec3( 0.0f,  1.0f,  0.0f);
	m_xVertices[3].position = glm::vec3(-1.0f, -1.0f, -1.0f);
	m_xVertices[4].position = glm::vec3( 1.0f, -1.0f, -1.0f);

	m_xVertices[0].color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_xVertices[1].color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m_xVertices[2].color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	m_xVertices[3].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_xVertices[4].color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

	m_xVertices[0].texcoords = glm::vec2(0.0f);
	m_xVertices[1].texcoords = glm::vec2(0.0f);
	m_xVertices[2].texcoords = glm::vec2(0.0f);
	m_xVertices[3].texcoords = glm::vec2(0.0f);
	m_xVertices[4].texcoords = glm::vec2(0.0f);

	m_iIndexCount = 3*6;
	m_iIndices = new GLuint[m_iIndexCount];
	m_iIndices[0] = 0;
	m_iIndices[1] = 1;
	m_iIndices[2] = 2;

	m_iIndices[3] = 3;
	m_iIndices[4] = 0;
	m_iIndices[5] = 2;

	m_iIndices[6] = 4;
	m_iIndices[7] = 3;
	m_iIndices[8] = 2;

	m_iIndices[9] = 1;
	m_iIndices[10] = 4;
	m_iIndices[11] = 2;

	m_iIndices[12] = 0;
	m_iIndices[13] = 3;
	m_iIndices[14] = 4;

	m_iIndices[15] = 0;
	m_iIndices[16] = 4;
	m_iIndices[17] = 1;

	//Set up OpenGL buffers
	//void* ptr = &m_xGLBuffers;

	glGenBuffers(2, (GLuint*)&m_xGLBuffers);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_xGLBuffers.vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_xGLBuffers.index);

	glBufferData(GL_ARRAY_BUFFER, sizeof(m_xVertices[0])*m_iVertexCount, m_xVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_iIndices[0])*m_iIndexCount, m_iIndices, GL_STATIC_DRAW);
	//glBufferStorage(GL_ARRAY_BUFFER, sizeof(m_xVertices[0])*m_iVertexCount, m_xVertices, 0);
	//glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_iIndices[0])*m_iIndexCount, m_iIndices, 0);
#pragma endregion Pyramid test code
	*/
}

Mesh::~Mesh() {

	/* MeshManger handles cleanup */
	//delete [] m_xVertices;
	//delete [] m_iIndices;

	//glDeleteBuffers(meshBufferIDs::length, (GLuint*)&m_xGLBuffers);
}

unsigned int Mesh::getVertexCount() const {

	return m_iVertexCount;
}

unsigned int Mesh::getIndexCount() const {

	return m_iIndexCount;
}

unsigned int Mesh::getTriCount() const {

	return m_iIndexCount / 3;
}

vertex* Mesh::getVertexArray() const {

	return m_xVertices;
}

GLuint* Mesh::getIndexArray() const {

	return m_iIndices;
}

GLuint Mesh::getVertexBufferID() {

	return m_xGLBuffers.vertex;
}

GLuint Mesh::getIndexBufferID() {

	return m_xGLBuffers.index;
}

void Mesh::setVertexArray( unsigned int vertCount, vertex* vertexArray ) {

	if(m_xVertices != nullptr)
		delete[] m_xVertices;
	m_iVertexCount = vertCount;
	m_xVertices = vertexArray;
}

void Mesh::setIndexArray( unsigned int indicesCount, GLuint* indexArray ) {

	if(m_iIndices != nullptr)
		delete[] m_iIndices;
	m_iIndexCount = indicesCount;
	m_iIndices = indexArray;
}

meshBufferIDs& Mesh::getBufferIDs() {

	return m_xGLBuffers;
}

bool Mesh::isDummy() {

	return m_iVertexCount == 0;
}
