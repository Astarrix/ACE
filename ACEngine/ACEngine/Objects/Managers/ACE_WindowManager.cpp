#include "ACE_WindowManager.h"

#include <iostream>
#include <ostream>
#include "SDL3_ttf/SDL_ttf.h"


ACE_WindowManager* ACE_WindowManager::instance = nullptr;

ACE_WindowManager::~ACE_WindowManager()
{
	CloseWindow();
	instance = nullptr;
}

ACE_WindowManager* ACE_WindowManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new ACE_WindowManager();
	}
	return instance;
}

bool ACE_WindowManager::CreateWindow()
{
	if (!SDL_CreateWindowAndRenderer(initTitle, 500, 500, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_TRANSPARENT, &window, &renderer))
	{
		std::cout << "Failed to create window and renderer" << "\n";
		SDL_Quit();
		return false;
	}
	SDL_GetWindowSize(window, &ScreenWidth, &ScreenHeight);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // set to allow for transparency

	return true;
}

void ACE_WindowManager::CloseWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	SDL_Quit();
	TTF_Quit();
}

void ACE_WindowManager::Update(std::function<void(float, SDL_Event)> callback, float deltaTime, SDL_Event event)
{
	ACE_Object::Update(deltaTime, event);
	callback(deltaTime, event);
}

void ACE_WindowManager::Render(std::function<void(SDL_Renderer*)> callback, SDL_Renderer* inRenderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(inRenderer);
	callback(inRenderer);
	SDL_RenderPresent(inRenderer);
}
