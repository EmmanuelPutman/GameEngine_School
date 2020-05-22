#pragma once
#include "Logger.h"
//#include <windows.h>
#pragma region

#include "AudioManager.h"

class Audio
{
public:
	Audio() = default;
	virtual ~Audio() = default;
	virtual void PlaySounds(int soundID) = 0;
	virtual void StopSound(int soundID) = 0;
	virtual void StopAllSounds() = 0;

protected:
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

};

class EmptyAudio final : public Audio
{
public:
	void PlaySounds(int) override {};
	void StopSound(int) override {};
	void StopAllSounds() override {};
};

class MutedAudio final : public Audio
{
public:
	MutedAudio() = default;

	void PlaySounds(int index) override 
	{ 
		Logger::GetInstance().Log("Audio: MUTED - Sound played with index: " + std::to_string(index)); 
	};
	void StopSound(int) override { Logger::GetInstance().Log("Audio: Sound stopped"); };
	void StopAllSounds() override { Logger::GetInstance().Log("Audio: All sounds stopped"); };
};

class NormalAudio final : public Audio
{
public:
	NormalAudio() = default;

	void PlaySounds(int index) override
	{
		AudioManager::GetInstance().GetSystem()->playSound(AudioManager::GetInstance().GetSound(index), 0, false, &m_pChannel);
	};
	void StopSound(int) override { Logger::GetInstance().Log("Audio: Sound stopped"); };
	void StopAllSounds() override { Logger::GetInstance().Log("Audio: All sounds stopped"); };
};


class ServiceLocator
{

public:
	static void Init() { audioService = &defaultAudioService; };
	static Audio& GetAudio() { return *audioService; };
	static void RegisterAudioService(Audio* service)
	{
		audioService = (service == nullptr) ? &defaultAudioService : service;
	}

private:
	static Audio* audioService;
	static EmptyAudio defaultAudioService;
};

