#include "Sprite2D.h"

Sprite2D::Sprite2D(SDL_Renderer* renderer) : Texture2D(renderer)
{
	this->renderer = renderer;
}

void Sprite2D::LoadSpriteSheetFromFile(std::string path, int inRows, int inColumns, int inCurrentRow, int inCurrentColumn)
{
	this->rows = inRows;
	this->columns = inColumns;
	//spriteSheet = new Texture2D(renderer);
	if (!LoadFromFile(path))
	{
		std::cout << "Unable to load sprite sheet" << std::endl;
		return;
	}
	spriteSheetHeight = GetHeight();
	spriteSheetWidth = GetWidth();
	spriteWidth = spriteSheetWidth / inColumns;
	spriteHeight = spriteSheetHeight / inRows;
	currentRow = inCurrentRow;
	currentColumn = inCurrentColumn;
	
}

void Sprite2D::RenderSprite(Vector2D position, SDL_FlipMode flip)
{
	spritePosition = position;
	Box2D src = {currentColumn * spriteWidth, currentRow * spriteHeight, spriteWidth, spriteHeight};
	Box2D dst = {position.x, position.y, spriteWidth, spriteHeight};
	//src.DrawDebugRect(renderer, Color::Red(), true);
	//dst.DrawDebugRect(renderer, Color::Blue(), true);
	Render(src, dst, flip, 0);
}

void Sprite2D::SetSpriteIndex(int spriteIndex)
{
	currentRow = spriteIndex / columns; // 2 & 1 = 0 
	currentColumn = spriteIndex % columns; // 2/3
}

void Sprite2D::PrintSpriteInfo()
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