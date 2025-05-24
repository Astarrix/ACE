#pragma once
#include "Objects/Components/Sub-Components/ACE_Texture2D.h"
#include "Commons/ACE_Vector2D.h"

struct SpriteData
{
	const char* path;
	int rows = 1;
	int columns = 1;

	SpriteData(const char* inPath, int inRows = 1, int inColumns = 1)
	{
		path = inPath;
		rows = inRows;
		columns = inColumns;
	}
};

class ACE_Sprite2D : public ACE_Texture2D
{
public:
	ACE_Sprite2D() = default;

	void LoadSpriteSheetFromFile(SDL_Renderer* inRenderer, SpriteData data, int inCurrentRow = 0, int inCurrentColumn = 0);
	void RenderSprite(SDL_FlipMode flip = SDL_FLIP_NONE);
	
	void SetSpriteIndex(int spriteIndex);
	
	int GetSpriteWidth() const { return spriteWidth; }
	int GetSpriteHeight() const { return spriteHeight; }
	bool IsInitialised() const { return isInitialised; }

protected:
	SDL_Renderer* renderer;

	bool isInitialised = false;
	int rows = 1;
	int columns = 1;
	int spriteWidth;
	int spriteHeight;
	int spriteSheetWidth;
	int spriteSheetHeight;
	const char* spriteSheetPath;

	int currentRow = 0;
	int currentColumn = 0;

	ACE_Vector2D spritePosition;

private:
};
