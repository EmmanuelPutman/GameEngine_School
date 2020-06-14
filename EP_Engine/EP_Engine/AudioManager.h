#pragma once
#include "Singleton.h"
#include <fmod.hpp>
#include <map>
#include <string>

using namespace ep;

class AudioManager : public Singleton<AudioManager>
{
public:
	AudioManager();
	~AudioManager();
	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator= (const AudioManager&) = delete;
	AudioManager& operator= (const AudioManager&&) = delete;

	void AddSound(int index, std::string fileName);
	void Update();
	
	FMOD::System* GetSystem() const;
	FMOD::Sound* GetSound(int index) const;

private:
	FMOD::System* m_pSystem;
	std::map<int, FMOD::Sound*> m_pSounds;
};

