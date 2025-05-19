#include <SDL3/SDL.h>
#include <iostream>

#include "ACE_EventManager.h"
#include "Characters/Character.h"
#include "Commons/ACE_Line2D.h"
#include "Managers/ACE_WindowManager.h"
#include "Managers/ACE_AudioManager.h"
#include "Managers/ACE_GameScreenManager.h"
#include "SDL3_ttf/SDL_ttf.h"


bool Update();
void Render();
void Close();

ACE_GameScreenManager* gameScreenManager;
ACE_WindowManager* windowManager;
ACE_EventManager* eventManager;
Uint32 gOldTime;

int main(int argc, char* argv[])
{
	// Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (!TTF_Init())
	{
		std::cout << "TTF could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	windowManager = new ACE_WindowManager();
	windowManager->CreateWindow();
	gameScreenManager = new ACE_GameScreenManager(windowManager->GetRenderer(), SCREEN_LEVEL1);
	eventManager = new ACE_EventManager();
	ACE_AudioManager::Instance()->LoadWav("audio/Mario.wav");
	gOldTime = SDL_GetTicks();
	// Main loop
	bool bIsGameRunning = true;
	while (bIsGameRunning)
	{
		bIsGameRunning = Update();
		Render();
	}
	Close();
	return 0;
}

bool Update()
{
	Uint32 NewTime = SDL_GetTicks();
	SDL_Event event;
	SDL_PollEvent(&event);


	switch (event.type) // game events
	{
	case SDL_EVENT_QUIT:
		return false;
		break;
	case SDL_EVENT_KEY_DOWN:
		switch (event.key.key) // keyboard events
		{
		case SDLK_ESCAPE:
			return false;
			break;
		case SDLK_F1:
			SDL_Event newEvent;
			newEvent.type = eventManager->GetEventLabel(ACE_EventManager::ACE_EVENT_COLLISION);
			newEvent.user.code = 1;
			newEvent.user.data1 = (ACE_WindowManager*)windowManager;
			SDL_PushEvent(&newEvent);
			break;
		}
		break;
	}
	eventManager->PollEvents(&event);
	gameScreenManager->Update((NewTime - gOldTime) / 1000.0f, &event);
	gOldTime = NewTime;
	return true;
}

void Render()
{
	SDL_SetRenderDrawColor(windowManager->GetRenderer(), 0X00, 0X00, 0X00, 0X00);
	SDL_SetRenderDrawBlendMode(windowManager->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_RenderClear(windowManager->GetRenderer());
	gameScreenManager->Render();
	SDL_RenderPresent(windowManager->GetRenderer());
}

void Close()
{
	delete gameScreenManager;
	gameScreenManager = nullptr;
	windowManager->CloseWindow();
	delete windowManager;
	windowManager = nullptr;
	TTF_Quit();
	SDL_Quit();
}
