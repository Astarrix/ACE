#pragma once
#include "components/ACE_Sprite2D.h"
#include "Commons/ACE_Box2D.h"
#include "components/ACE_Texture2D.h"
#include "Managers/ACE_LevelMap.h"

class POW_Block
{
public:
	POW_Block(SDL_Renderer* renderer, ACE_LevelMap* map);
	~POW_Block();
	void Render();
	ACE_Box2D GetCollisionBox();
	void TakeHit();
	bool isAvailable();
private:
	SDL_Renderer* renderer;
	ACE_Vector2D position;
	ACE_Sprite2D* sprite;
	ACE_LevelMap* levelMap;

	float singleSprite_w;
	float singleSprite_h;
	int numHitsRemaining;
};
