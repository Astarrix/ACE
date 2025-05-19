#include "ACE_AudioManager.h"

#include <iostream>
#include <ostream>

ACE_AudioManager* ACE_AudioManager::instance = nullptr;
ACE_AudioManager::~ACE_AudioManager()
{
	instance = nullptr;
	SDL_free(wav_data);
	SDL_DestroyAudioStream(stream);
	stream = nullptr;
}

ACE_AudioManager* ACE_AudioManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new ACE_AudioManager();
		// open Audio
	}
	return instance;
}

ACE_AudioManager::ACE_AudioManager()
{

}

void ACE_AudioManager::LoadWav(const char* filePath)
{
	// Clean up previous Audio data and stream
	if (wav_data) {
		SDL_free(wav_data);
		wav_data = nullptr;
	}

	// Load new Audio
	if (!SDL_LoadWAV(filePath, &audioSpec, &wav_data, &wav_data_len)) {
		std::cout << "Error loading wav file. Error: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_MixAudio(wav_data, wav_data, SDL_AUDIO_S16, wav_data_len, volume);

	// Create a new stream
	stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec, nullptr, nullptr);
	if (!stream) {
		std::cout << "Error opening Audio stream. Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Queue the Audio data once
	SDL_PutAudioStreamData(stream, wav_data, wav_data_len);
        
	// Start playback
	if (!SDL_ResumeAudioStreamDevice(stream)) {
		std::cout << "Error resuming Audio stream. Error: " << SDL_GetError() << std::endl;
		return;
	}
}

void ACE_AudioManager::SetVolume(float volume)
{
	this->volume = volume;
}
