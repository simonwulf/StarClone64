#include "stdafx.h"
#include "ModelManager.h"
#include "LogManager.h"

ModelManager ModelManager::m_sInstance;

ModelManager::ModelManager() {

}

ModelManager* ModelManager::instance() {

	return &m_sInstance;
}

Model* ModelManager::getModel(std::string filepath, unsigned int loadFlags) {

	ModelMap::iterator found = m_xModelCache.find(filepath);
	Model* ret;

	if (found == m_xModelCache.end()) {
	
		ret = new Model(filepath, loadFlags);
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

ModelManager::~ModelManager() {

	clearCache();
}
