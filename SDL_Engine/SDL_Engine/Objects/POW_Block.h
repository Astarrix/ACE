#pragma once
#include "Sprite2D.h"
#include "commons/Box2D.h"
#include "commons/Texture2D.h"
#include "Managers/LevelMap.h"

class POW_Block
{
public:
	POW_Block(SDL_Renderer* renderer, LevelMap* map);
	~POW_Block();
	void Render();
	Box2D GetCollisionBox();
	void TakeHit();
	bool isAvailable();
private:
	SDL_Renderer* renderer;
	Vector2D position;
	Sprite2D* sprite;
	LevelMap* levelMap;

	float singleSprite_w;
	float singleSprite_h;
	int numHitsRemaining;
};
