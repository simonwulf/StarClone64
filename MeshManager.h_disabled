#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include "Mesh.h"
#include <unordered_map>

class MeshManager {

	public:
		~MeshManager();

		static MeshManager& getInstance(){ return m_instance; }
		static void clearCache();

		static Mesh* getMesh(std::string meshName, unsigned int loadFlags = 0);
		

	private:
		MeshManager();
		MeshManager(const MeshManager&);
		void operator=(const MeshManager&);

		static MeshManager m_instance;
		std::unordered_map<std::string, Mesh*>* m_meshTable;

		void loadMesh(std::string meshName, unsigned int loadFlags = 0);
};

#endif