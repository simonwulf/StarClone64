#include "AudioManager.h"
#include "LogManager.h"
#include <FMOD/fmod_errors.h>

AudioManager AudioManager::m_sInstance;

AudioManager::AudioManager() {

	m_xGlobalListener = nullptr;
	m_sBasePath = "data/audio"; //TODO: read from config
	if(m_sBasePath[m_sBasePath.size()-1] != '\\')
		m_sBasePath += '\\';
	checkError( FMOD::System_Create(&m_xAudioEngine) );
	FMOD_SPEAKERMODE speakermode;
	checkError( m_xAudioEngine->getDriverCaps(0, 0, 0, &speakermode) );
	checkError( m_xAudioEngine->setSpeakerMode(speakermode) );
	checkError( m_xAudioEngine->init(32, FMOD_INIT_NORMAL, 0) );
	checkError( m_xAudioEngine->set3DSettings(0.0f, 1.0f, 1.0f) );
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

	m_xAudioTable.clear();
	Log::Writeln("AudioManager cache cleared");
}

unsigned int AudioManager::loadAudio( std::string path ) {

	Log::Writeln("Loading audio " + path);

	FMOD::Sound* sound;
	checkError( m_xAudioEngine->createSound(std::string(m_sBasePath + path).c_str(), FMOD_3D, 0, &sound) );
	
	soundData sd;
	sd.sound = sound;
	sd.name = path;
	m_xAudioTable.push_back(sd);

	return m_xAudioTable.size();
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

	std::stringstream ss;
	ss << "Listener: " << fv_listener_position.x << "\t, " <<
		fv_listener_position.y << "\t, " << fv_listener_position.z
		<< "\tSource: " << fv_position.x << "\t, " << fv_position.y <<
		"\t, " << fv_position.z;

	Log::Writeln(ss.str(), Log::COLOR_LIGHT_AQUA);
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
