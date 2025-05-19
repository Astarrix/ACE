#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, ACE_Vector2D position)
{
	this->position = position;
	this->renderer = renderer;
	sprite = new ACE_Sprite2D(renderer);
	sprite->LoadSpriteSheetFromFile(SpriteData("images/Coin.png", 1, 3));
	animator = new ACE_Animator(sprite, 0, 2, 0.25f);
	animator->Begin(true);
}

Coin::~Coin()
{
	renderer = nullptr;
	delete sprite;
	sprite = nullptr;
	delete animator;
	animator = nullptr;
}

void Coin::Render()
{
	animator->Render(position, SDL_FLIP_NONE);
}

void Coin::Update(float deltaTime)
{
	animator->Update(deltaTime);
}
