#include "ACE_Tile.h"

ACE_Tile::ACE_Tile()
{
	spriteData = SpriteData("Resources/images/PowBlock.png", 1, 3);
	friendlyName = "Tile";
	hasCollision = true;
	hasGravity = false;
	isStaticMove = true;
}

void ACE_Tile::Init()
{
	ACE_Actor::Init();
	spriteComponent->SetSpriteIndex(2);
	animator = new ACE_Animator(spriteComponent, 0, 2, 3);
	animator->Begin(true);
}

void ACE_Tile::Update(float deltaTime, SDL_Event event)
{
	ACE_Actor::Update(deltaTime, event);
	animator->Update(deltaTime);
}

void ACE_Tile::Render(SDL_Renderer* renderer)
{
	//ACE_Actor::Render(renderer);
	animator->Render(SDL_FLIP_NONE);
}
