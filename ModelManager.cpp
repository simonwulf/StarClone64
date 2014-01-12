#include "stdafx.h"
#include "ModelManager.h"
#include "LogManager.h"
#include <Shlwapi.h>

ModelManager ModelManager::m_sInstance;

ModelManager::ModelManager() {

	m_xModelBase = "data/models";
}

ModelManager* ModelManager::instance() {

	return &m_sInstance;
}

Model* ModelManager::getModel(std::string filepath, unsigned int loadFlags) {

	ModelMap::iterator found = m_xModelCache.find(filepath);
	Model* ret;

	if (found == m_xModelCache.end()) {
	
		char modelPath[MAX_PATH];
		PathCombineA(modelPath, m_xModelBase.c_str(), filepath.c_str());
		ret = new Model(std::string(modelPath), loadFlags);
		m_xModelCache[filepath] = ret;
	
	} else {
	
		ret = found->second;
	}

	return ret;
}

void ModelManager::clearCache() {

	/* Loops the mesh table and free data held by the meshes */
	for(ModelMap::iterator it = m_xModelCache.begin(); it != m_xModelCache.end(); ++it) {

		//std::string meshName = it->first;
		delete it->second;
	}

	m_xModelCache.clear();
	Log::Writeln("ModelManager cache cleared");
}