#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <string>
#include <unordered_map>

#include "Model.h"

class ModelManager {

  public:

	~ModelManager();
	static ModelManager* instance();

	Model* getModel(std::string filepath, unsigned int loadFlags = 0);

	void clearCache();

  private:
	
	ModelManager();
	ModelManager(const ModelManager&);

	static ModelManager m_sInstance;

	typedef std::unordered_map<std::string, Model*> ModelMap;
	ModelMap m_xModelCache;
};

#endif