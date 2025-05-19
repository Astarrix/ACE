#include "ACE_Sprite2D.h"

ACE_Sprite2D::ACE_Sprite2D(SDL_Renderer* renderer) : ACE_Texture2D(renderer)
{
}

void ACE_Sprite2D::LoadSpriteSheetFromFile(SpriteData data, int inCurrentRow, int inCurrentColumn)
{
	this->spriteSheetPath = data.path;
	this->rows = data.rows;
	this->columns = data.columns;
	if (!LoadFromFile(spriteSheetPath.c_str()))
	{
		std::cout << "Unable to load sprite sheet" << std::endl;
		isInitialised = false;
		return;
	}
	spriteSheetHeight = GetHeight();
	spriteSheetWidth = GetWidth();
	spriteWidth = spriteSheetWidth / data.columns;
	spriteHeight = spriteSheetHeight / data.rows;
	currentRow = inCurrentRow;
	currentColumn = inCurrentColumn;
	isInitialised = true;
}

void ACE_Sprite2D::RenderSprite(ACE_Vector2D position, SDL_FlipMode flip)
{
	spritePosition = position;
	ACE_Box2D src = {currentColumn * spriteWidth, currentRow * spriteHeight, spriteWidth, spriteHeight};
	ACE_Box2D dst = {position.x, position.y, spriteWidth, spriteHeight};
	Render(src, dst, flip, 0);
}

void ACE_Sprite2D::SetSpriteIndex(int spriteIndex)
{
	// if (spriteIndex < 1 || spriteIndex >= rows * columns)
	// {
	// 	std::cout << "INVALID SPRITE INDEX: " << spriteIndex << " IN " << spriteSheetPath << std::endl;
	// 	return;
	// }
	currentRow = spriteIndex / columns;
	currentColumn = spriteIndex % columns;
}

void ACE_Sprite2D::PrintSpriteInfo()
{
	std::cout << "Rows: " << rows << std::endl;
	std::cout << "Columns: " << columns << std::endl;
	std::cout << "Current Row: " << currentRow << std::endl;
	std::cout << "Current Column: " << currentColumn << std::endl;
	std::cout << "Sprite Sheet Width: " << spriteSheetWidth << std::endl;
	std::cout << "Sprite Sheet Height: " << spriteSheetHeight << std::endl;
	std::cout << "Sprite Width: " << spriteWidth << std::endl;
	std::cout << "Sprite Height: " << spriteHeight << std::endl;
	std::cout << "Sprite Position: " << currentRow * spriteWidth << ", " << currentColumn * spriteHeight << std::endl;
}