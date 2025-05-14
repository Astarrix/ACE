#pragma once
#include "Characters/Character.h"

class Character_Mario : public Character
{
public:
	Character_Mario(SDL_Renderer* renderer, std::string imgPath, Vector2D initPosition = Vector2D(0.0, 0.0), LevelMap* map = nullptr);
	void Update(float deltaTime, SDL_Event* event) override;
};
