#pragma once
#include "components/ACE_Animator.h"
#include "components/ACE_Sprite2D.h"
#include "Commons/ACE_Vector2D.h"
#include "SDL3/SDL.h"

class Coin
{
public:
	Coin(SDL_Renderer* renderer, ACE_Vector2D position);
	~Coin();
	void Render();
	void Update(float deltaTime);
private:
	SDL_Renderer* renderer;
	ACE_Vector2D position;
	ACE_Sprite2D* sprite;
	ACE_Animator* animator;
};
