#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "MeshData.h"

class SubMesh {

	public:

		SubMesh();
		SubMesh(std::vector<Vertex>* vertexData, std::vector<GLuint>* indexData, std::vector<Texture>* textureData = nullptr);
		~SubMesh();

		void draw(GLuint shader);

		const GLuint getVBO(){ return m_iVBO; }
		const GLuint getIND(){ return m_iIND; }
		const GLuint getICount() { return m_iIndices.size(); }

	private:

		std::vector<Vertex> m_xVertices;
		std::vector<Texture> m_xTextures;
		std::vector<GLuint> m_iIndices;
		GLuint m_iVBO, m_iIND;

};

class Mesh {

	public:
		Mesh();
		~Mesh();

		std::vector<SubMesh*>* m_xMeshes;

		void draw(GLuint shader);

		void quickTestDraw();
};

#endif