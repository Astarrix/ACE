#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

#include "Objects/Managers/ACE_GameMode.h"
#include "Objects/Managers/ACE_WindowManager.h"

Uint64 g_OldTime = SDL_GetTicks();

bool HasUserExited(SDL_Event &event);

int main(int argc, char* argv[])
{
	// Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	if (!TTF_Init())
	{
		std::cout << "TTF could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	ACE_WindowManager::Instance()->CreateWindow();									// create window
	ACE_GameMode* gameMode = new ACE_GameMode(ACE_WindowManager::Instance());		// create game mode (top level manager for game)
	ACE_Map* map = new ACE_Map();													// create map (contains all actors and positions to render them at)
	
	gameMode->GameBegin(map); // load map that we are using, right now its using a map base class
	
	SDL_Event l_event;
	float l_deltaTime = 0.0f;
	ACE_Vector2D windowSize = ACE_WindowManager::Instance()->GetWindowSize();
	std::cout << "Window X: " << windowSize.x << " Window Y: " << windowSize.y << "\n";
	
	while (HasUserExited(l_event) == false)
	{
		ACE_WindowManager::Instance()->Update([&](float, SDL_Event) { gameMode->Update(l_deltaTime, l_event); }, l_deltaTime, l_event);
		ACE_WindowManager::Instance()->Render([&](SDL_Renderer* renderer) { gameMode->Render(renderer); }, ACE_WindowManager::Instance()->GetRenderer());
		
		Uint64 l_newTime = SDL_GetTicks();
		l_deltaTime = (l_newTime - g_OldTime) * 0.001f;
		g_OldTime = l_newTime;

	}
	ACE_WindowManager::Instance()->CloseWindow();

	return 0;
}

/**
 * @brief checks if game was exited
 * @param event outParam that loads the event into it after its been polled to be passed down to the proceeding functions
 * @return returns true if game was exited
 */
bool HasUserExited(SDL_Event &event)
{
	SDL_Event l_event;
	SDL_PollEvent(&l_event);
	
	switch (l_event.type)
	{
	case SDL_EVENT_QUIT:
		return true;
		break;
	case SDL_EVENT_KEY_DOWN:
		switch (l_event.key.key)
		{
		case SDLK_ESCAPE:
			return true;
			break;
		}
		break;
	}
	event = l_event;
	return false;
}