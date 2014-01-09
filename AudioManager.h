#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <FMOD/fmod.hpp>
#include "GameObject.h"

class AudioManager {

	public:

		~AudioManager();

		static AudioManager* instance();
		void clearCache();

		void playAudio(unsigned int index, glm::vec3 position);
		void playAudio(unsigned int index, GameObject* source);
		FMOD::Sound* getAudio(unsigned int index);
		unsigned int getIndexByName(std::string name);
		unsigned int loadAudio(std::string path);

		void update();
		void setGlobalListener(GameObject* listener);

	private:

		AudioManager();
		AudioManager(const AudioManager&);
		void operator=(const AudioManager&);

		static AudioManager m_sInstance;

		struct soundData {
			FMOD::Sound* sound;
			std::string name;
		};

		std::vector<soundData> m_xAudioTable;

		std::string m_sBasePath;
		FMOD::System* m_xAudioEngine;
		GameObject* m_xGlobalListener;

		void checkError(FMOD_RESULT result);

		const FMOD_VECTOR glmToFmod(glm::vec3 v) const {

			FMOD_VECTOR f = { v.x, v.y, v.z };
			return f;
		}
};

#endif
