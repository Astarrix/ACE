#pragma once
#include "Components/ACE_Texture2D.h"

struct SpriteData
{
	std::string path;
	int rows = 1;
	int columns = 1;

	SpriteData(std::string inPath, int inRows = 1, int inColumns = 1)
	{
		path = inPath;
		rows = inRows;
		columns = inColumns;
	}
};

class ACE_Sprite2D : public ACE_Texture2D
{
public:
	ACE_Sprite2D(SDL_Renderer* renderer);

	void LoadSpriteSheetFromFile(SpriteData data, int inCurrentRow = 0, int inCurrentColumn = 0);
	void RenderSprite(ACE_Vector2D position, SDL_FlipMode flip = SDL_FLIP_NONE);
	void SetSpriteIndex(int spriteIndex);
	float GetSpriteWidth() const {return spriteWidth;}
	float GetSpriteHeight() const {return spriteHeight;}
	void PrintSpriteInfo();
	bool IsInitialised() const {return isInitialised;}
protected:
	SDL_Renderer* renderer;
	
	bool isInitialised = false;
	int rows;
	int columns;
	float spriteWidth;
	float spriteHeight;
	float spriteSheetWidth;
	float spriteSheetHeight;
	std::string spriteSheetPath;
	
	int currentRow = 0;
	int currentColumn = 0;

	ACE_Vector2D spritePosition;

private:
};