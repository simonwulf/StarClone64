#include "AudioManager.h"
#include "LogManager.h"
#include <FMOD/fmod_errors.h>

AudioManager AudioManager::m_sInstance;

AudioManager::AudioManager() {

	m_xGlobalListener = nullptr;
	m_xCurrentMusic = nullptr;
	m_sBasePath = "data/audio"; //TODO: read from config
	if(m_sBasePath[m_sBasePath.size()-1] != '\\')
		m_sBasePath += '\\';
	checkError( FMOD::System_Create(&m_xAudioEngine) );
	FMOD_SPEAKERMODE speakermode;
	checkError( m_xAudioEngine->getDriverCaps(0, 0, 0, &speakermode) );
	checkError( m_xAudioEngine->setSpeakerMode(speakermode) );
	checkError( m_xAudioEngine->init(32, FMOD_INIT_NORMAL, 0) );
	checkError( m_xAudioEngine->set3DSettings(0.0f, 1.0f, 0.25f) );
}

AudioManager::~AudioManager() {

	clearCache();
	m_xAudioEngine->release();
}

void AudioManager::checkError( FMOD_RESULT result ) {

	if(result != FMOD_OK) {

		Log::Err("FMOD Error: " + std::string(FMOD_ErrorString(result)));
	}
}

void AudioManager::clearCache() {

	for(unsigned int i = 0; i < m_xAudioTable.size(); ++i) {
		m_xAudioTable[i].sound->release();
	}

	auto it = m_xMusicTable.begin();
	for(; it != m_xMusicTable.end(); ++it) {
		it->second->release();
	}

	m_xAudioTable.clear();
	m_xMusicTable.clear();
	Log::Writeln("AudioManager cache cleared");
}

unsigned int AudioManager::loadAudio( std::string path ) {

	Log::Writeln("Loading audio " + path);

	FMOD::Sound* sound;
	checkError( m_xAudioEngine->createSound(std::string(m_sBasePath + path).c_str(), FMOD_3D | FMOD_HARDWARE | FMOD_LOOP_OFF, 0, &sound) );
	
	soundData sd;
	sd.sound = sound;
	sd.name = path;
	m_xAudioTable.push_back(sd);

	return m_xAudioTable.size();
}

FMOD::Sound* AudioManager::loadMusic( std::string name ) {

	Log::Writeln("Loading music " + name);

	FMOD::Sound* music;
	checkError( m_xAudioEngine->createStream(std::string(m_sBasePath + name).c_str(), FMOD_HARDWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &music) );

	m_xMusicTable.insert( std::make_pair(name, music) );

	return music;
}


unsigned int AudioManager::getIndexByName( std::string name ) {

	for(unsigned int i = 0; i < m_xAudioTable.size(); ++i) {

		if(m_xAudioTable[i].name == name)
			return (i+1);
	}

	return 0;
}

void AudioManager::playAudio( unsigned int index, glm::vec3 position) {

	FMOD::Channel* channel;
	FMOD_VECTOR fv_position = glmToFmod(position);
	FMOD_VECTOR fv_listener_position = { 0, 0, 0 };
	FMOD_VECTOR fv_velocity = { 0, 0, 0 };
	FMOD_VECTOR fv_forward = { 0, 0, 0 };
	FMOD_VECTOR fv_up = { 0, 0, 0 };
	if(m_xGlobalListener != nullptr) {

		fv_listener_position = glmToFmod(m_xGlobalListener->getWorldPosition());
		fv_velocity = glmToFmod(glm::vec3(0));
		fv_forward = glmToFmod(-m_xGlobalListener->forward());
		fv_up = glmToFmod(m_xGlobalListener->up());
	}
	m_xAudioEngine->set3DListenerAttributes(0, &fv_listener_position, &fv_velocity, &fv_forward, &fv_up);
	m_xAudioEngine->playSound(FMOD_CHANNEL_FREE, m_xAudioTable[index-1].sound, true, &channel);
	channel->set3DAttributes(&fv_position, &fv_velocity);
	channel->setPaused(false);
}

void AudioManager::playAudio( unsigned int index, GameObject* source ) {

	if(source != nullptr) {

		playAudio(index, source->getWorldPosition());
	}
}

FMOD::Sound* AudioManager::getAudio( unsigned int index ) {

	return m_xAudioTable[index-1].sound;
}

void AudioManager::update() {

	if(m_xAudioEngine != nullptr) {

		m_xAudioEngine->update();
	}
}

AudioManager* AudioManager::instance() {

	return &m_sInstance;
}

void AudioManager::setGlobalListener( GameObject* listener ) {

	m_xGlobalListener = listener;
}

void AudioManager::playMusic( std::string name ) {

	auto it = m_xMusicTable.find(name);
	FMOD::Sound* music;

	if (it == m_xMusicTable.end()) {

		music = loadMusic(name);
	} else {

		music = it->second;
	}

	if(m_xCurrentMusic != nullptr) {

		m_xCurrentMusic->release();
	}

	m_xCurrentMusic = music;
	m_xAudioEngine->playSound(FMOD_CHANNEL_FREE, music, false, 0);
}
