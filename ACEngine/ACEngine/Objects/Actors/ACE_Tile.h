#pragma once
#include "ACE_Actor.h"
#include "Objects/Components/Sub-Components/ACE_Animator.h"

class ACE_Tile : public ACE_Actor
{
public:
	ACE_Tile();
	void Init() override;
	ACE_Animator* animator = nullptr;
	void Update(float deltaTime, SDL_Event event) override;
	void Render(SDL_Renderer* renderer) override;
};
