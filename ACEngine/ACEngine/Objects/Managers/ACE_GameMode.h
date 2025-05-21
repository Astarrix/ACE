#pragma once
#include "ACE_WindowManager.h"
#include "Objects/ACE_Object.h"
#include "Objects/Maps/ACE_Map.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"

class ACE_GameMode : public ACE_Object
{
public:
	ACE_GameMode(ACE_WindowManager* windowManager);
	~ACE_GameMode() override;
	
	void Update(float deltaTime, SDL_Event event) override;
	void Render(SDL_Renderer* renderer);
	void GameBegin(ACE_Map* startMap);
	void GameEnd();
private:
	ACE_Map* currentMap = nullptr;
	ACE_WindowManager* windowManager = nullptr;
	void UpdateMap(float deltaTime, SDL_Event event);
	void RenderMap(SDL_Renderer* renderer);
};
