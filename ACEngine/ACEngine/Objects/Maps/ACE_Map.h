#pragma once
#include <vector>

#include "Objects/ACE_Object.h"
#include "Objects/Actors/ACE_Actor.h"

class ACE_Map : public ACE_Object
{
public:
	ACE_Map() = default;
	~ACE_Map() override;
	bool SpawnActor(ACE_Transform2D transform, ACE_Actor* actor);
	void Update(float deltaTime, SDL_Event event) override;
	void Render(SDL_Renderer* renderer);
	void Init() override;
private:
	std::vector<ACE_Actor*> actors;
	void UpdateActors(float deltaTime, SDL_Event event);
	void RenderActors(SDL_Renderer* renderer);
};
