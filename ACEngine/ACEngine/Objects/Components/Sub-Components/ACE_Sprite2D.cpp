#include "ACE_Sprite2D.h"



void ACE_Sprite2D::LoadSpriteSheetFromFile(SDL_Renderer* inRenderer, SpriteData data, int inCurrentRow, int inCurrentColumn)
{
	if (inRenderer == nullptr)
	{
		std::cout << "Renderer is null on sprite: " << data.path << "\n";
		return;
	}
	this->renderer = inRenderer;
	if (!LoadTextureFromFile(inRenderer, data.path))
	{
		std::cout << "Failed to load texture: " << data.path << "\n";
		return;
	}
	
	this->spriteSheetPath	= data.path;						
	this->columns			= data.columns;						
	this->rows				= data.rows;
	this->spriteWidth		= GetTextureWidth() / data.columns;
	this->spriteHeight		= GetTextureHeight() / data.rows;
	this->currentRow		= inCurrentRow;
	this->currentColumn		= inCurrentColumn;
	isInitialised = true;
}

void ACE_Sprite2D::RenderSprite(SDL_FlipMode flip)
{
	SDL_FRect portion =
		{
			float(currentColumn * spriteWidth),
			float(currentRow * spriteHeight),
			float(spriteWidth),
			float(spriteHeight)
		};
	RenderPortion(portion, flip);
}

void ACE_Sprite2D::SetSpriteIndex(int spriteIndex)
{
	currentRow = spriteIndex / columns;
	currentColumn = spriteIndex % columns;
}
