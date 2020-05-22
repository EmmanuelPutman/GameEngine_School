#include "EP_Engine_PCH.h"
#include "AudioManager.h"
#include "Logger.h"
#include <fmod_errors.h>

using namespace ep;

AudioManager::AudioManager()
	:m_pSystem{ nullptr }
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_pSystem);
	if (result != FMOD_OK)
	{
		Logger::GetInstance().Error("AudioManager: Creation of system not ok!");
	}
	else
		Logger::GetInstance().Warning("AudioManager: System Created!");

	result = m_pSystem->init(512, FMOD_INIT_NORMAL, 0);

	if (result != FMOD_OK)
	{
		Logger::GetInstance().Error("AudioManager: Initialization not ok!");
	}
	else
		Logger::GetInstance().Warning("AudioManager: System Initialized!");
}

AudioManager::~AudioManager()
{
	if (m_pSystem) m_pSystem->release();
}

void AudioManager::Update()
{
	m_pSystem->update();
}

FMOD::System* AudioManager::GetSystem() const
{
	return m_pSystem;
}

FMOD::Sound* AudioManager::GetSound(int index) const
{
	for (std::pair<int, FMOD::Sound*> sound : m_pSounds)
	{
		if (sound.first == index)
		{
			if (sound.second != nullptr)
				return sound.second;
		}
	}

	std::string err = "AudioManager: No sound was found at this index: ";
	err += std::to_string(index);
	Logger::GetInstance().Error( err );
	return nullptr;
}

void AudioManager::AddSound(int index, std::string fileName)
{
	for (std::pair<int, FMOD::Sound*> sound : m_pSounds)
	{
		if (sound.first == index)
		{
			Logger::GetInstance().Error("AudioManager: This index already has a sound! " + std::to_string(index));
			return;
		}
	}

	m_pSounds.insert(std::pair<int, FMOD::Sound*>(index, nullptr));

	FMOD_RESULT result;
	result = m_pSystem->createStream(fileName.c_str(), FMOD_DEFAULT, 0, &m_pSounds[index]);

	if (result != FMOD_OK)
	{
		Logger::GetInstance().Error("AudioManager: Added sound: " + std::string(FMOD_ErrorString(result)));
	}
}
