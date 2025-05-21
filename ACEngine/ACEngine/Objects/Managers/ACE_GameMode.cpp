#include "ACE_GameMode.h"

ACE_GameMode::ACE_GameMode(ACE_WindowManager* windowManager) : ACE_Object()
{
	this->windowManager = windowManager;
}

ACE_GameMode::~ACE_GameMode()
{
	delete currentMap;
	currentMap = nullptr;
	windowManager = nullptr;
}

void ACE_GameMode::Update(float deltaTime, SDL_Event event)
{
	ACE_Object::Update(deltaTime, event);
	UpdateMap(deltaTime, event);
}

void ACE_GameMode::Render(SDL_Renderer* renderer)
{
	RenderMap(renderer);
}

void ACE_GameMode::GameBegin(ACE_Map* startMap)
{
	currentMap = startMap;
	currentMap->Init();
}

void ACE_GameMode::GameEnd()
{
	
}

void ACE_GameMode::UpdateMap(float deltaTime, SDL_Event event)
{
	if (currentMap == nullptr) { return; }
	currentMap->Update(deltaTime, event);
}

void ACE_GameMode::RenderMap(SDL_Renderer* renderer)
{
	if (currentMap == nullptr) { return; }
	currentMap->Render(renderer);
}
