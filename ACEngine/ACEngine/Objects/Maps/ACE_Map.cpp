#include "ACE_Map.h"

#include "Objects/Actors/ACE_Character.h"
#include "Objects/Actors/ACE_Player.h"
#include "Objects/Managers/ACE_EventSystem.h"


ACE_Map::~ACE_Map()
{
	for (ACE_Actor* actor : this->actors)
	{
		delete actor;
		actor = nullptr;
	}
}

bool ACE_Map::SpawnActor(ACE_Transform2D transform, ACE_Actor* actor)
{
	actor->SetTransform(transform);
	this->actors.push_back(actor);
	return true;
}

void ACE_Map::Update(float deltaTime, SDL_Event event)
{
	ACE_Object::Update(deltaTime, event);
	UpdateActors(deltaTime, event);
}

void ACE_Map::Render(SDL_Renderer* renderer)
{
	RenderActors(renderer);
}

void ACE_Map::Init()
{
	ACE_Object::Init();
	ACE_Player* newActor = new ACE_Player();
	SpawnActor(newActor->GetTransform(), newActor);
	InitActors();
}

void ACE_Map::InitActors()
{
	for (ACE_Actor* actor : this->actors)
	{
		actor->Init();
	}
}

void ACE_Map::UpdateActors(float deltaTime, SDL_Event event)
{
	for (ACE_Actor* actor : this->actors)
	{
		actor->Update(deltaTime, event);
	}
}

void ACE_Map::RenderActors(SDL_Renderer* renderer)
{
	for (ACE_Actor* actor : this->actors)
	{
		actor->Render(renderer);
	}
}
