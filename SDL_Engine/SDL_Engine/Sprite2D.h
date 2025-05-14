#pragma once
#include "commons/Texture2D.h"

class Sprite2D : public Texture2D
{
public:
	Sprite2D(SDL_Renderer* renderer);

	void LoadSpriteSheetFromFile(std::string path, Vector2D spriteSize, int rows, int columns, int currentRow = 0, int currentColumn = 0);
	void RenderSprite(Vector2D position, SDL_FlipMode flip);
protected:
	SDL_Renderer* renderer;
	Texture2D* spriteSheet; 
	
	int rows;
	int columns;
	float spriteWidth;
	float spriteHeight;
	float spriteSheetWidth;
	float spriteSheetHeight;

	int currentRow = 0;
	int currentColumn = 0;

	void SetSpriteIndex(int spriteIndex);
private:

};

/*
* 		float left = singleSprite_w * (numHitsRemaining - 1);
		Box2D portionOfSprite = {left, 0, singleSprite_w, singleSprite_h};
		Box2D destination = {position.x, position.y, singleSprite_w, singleSprite_h};
		texture->Render(portionOfSprite, destination, SDL_FLIP_NONE, 0, false);
 */