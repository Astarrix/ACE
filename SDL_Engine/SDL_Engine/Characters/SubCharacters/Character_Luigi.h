#pragma once
#include <string>

#include "Characters/Character.h"

class Character_Luigi : public Character
{
public:
	Character_Luigi(SDL_Renderer* renderer, SpriteData spriteData, ACE_Vector2D initPosition = ACE_Vector2D(0.0, 0.0), ACE_LevelMap* map = nullptr);
	void Update(float deltaTime, SDL_Event* event) override;
};
