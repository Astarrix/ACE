#include "Sprite2D.h"

Sprite2D::Sprite2D(SDL_Renderer* renderer) : Texture2D(renderer)
{
	this->renderer = renderer;
}

void Sprite2D::LoadSpriteSheetFromFile(std::string path, Vector2D spriteSize, int rows, int columns, int currentRow, int currentColumn)
{
	spriteSheet = new Texture2D(renderer);
	if (!spriteSheet->LoadFromFile(path))
	{
		std::cout << "Unable to load sprite sheet" << std::endl;
		return;
	}
	spriteWidth = spriteSize.x;
	spriteHeight = spriteSize.y;
	this->rows = rows;
	this->columns = columns;
	spriteSheetHeight = spriteSheet->GetHeight();
	spriteSheetWidth = spriteSheet->GetWidth();
	
}

void Sprite2D::RenderSprite(Vector2D position, SDL_FlipMode flip)
{
	Box2D src = {currentRow * spriteWidth, currentColumn * spriteHeight, spriteWidth, spriteHeight};
	Box2D dst = {position.x, position.y, spriteWidth, spriteHeight};
	Render(src, dst, flip, 0);
}

void Sprite2D::SetSpriteIndex(int spriteIndex)
{
	currentRow = spriteIndex % columns;
	currentColumn = spriteIndex / columns;
}
