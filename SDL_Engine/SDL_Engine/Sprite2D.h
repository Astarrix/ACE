#pragma once
#include "commons/Texture2D.h"

class Sprite2D : public Texture2D
{
public:
	Sprite2D(SDL_Renderer* renderer);

	void LoadSpriteSheetFromFile(std::string path, int inRows, int inColumns, int inCurrentRow = 0, int inCurrentColumn = 0);
	void RenderSprite(Vector2D position, SDL_FlipMode flip = SDL_FLIP_NONE);
	void SetSpriteIndex(int spriteIndex);
	float GetSpriteWidth() {return spriteWidth;}
	float GetSpriteHeight() {return spriteHeight;}
	void PrintSpriteInfo();
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

	Vector2D spritePosition;

private:
};