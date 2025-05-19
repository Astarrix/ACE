#pragma once
#include "SDL3/SDL.h"

class ACE_AudioManager
{
public:
	~ACE_AudioManager();
	static ACE_AudioManager* Instance();
	void LoadWav(const char* filePath);
	void Update();
	void SetVolume(float volume);
	
	SDL_AudioStream* stream = nullptr;
	Uint8* wav_data = nullptr;
	Uint32 wav_data_len = 0;
	SDL_AudioSpec audioSpec;
	float volume = 1.0f;
private:
	ACE_AudioManager();
	static ACE_AudioManager* instance;

	
};
