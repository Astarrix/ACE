#include "ACE_Map.h"

#include "Objects/Actors/ACE_Character.h"
#include "Objects/Actors/ACE_Player.h"
#include "Objects/Actors/ACE_Tile.h"
#include "Objects/Managers/ACE_CollisionManager.h"
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
	actor->Init();
	if (actor->hasCollision)
	{
		ACE_CollisionManager::getInstance()->AddActor(actor);
	}
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
	ACE_Tile* newTile = new ACE_Tile();
	ACE_Transform2D newTransform = ACE_Transform2D({200, 975});
	SpawnActor(newTransform, newTile);
	SpawnActor(newActor->GetTransform(), newActor);
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
