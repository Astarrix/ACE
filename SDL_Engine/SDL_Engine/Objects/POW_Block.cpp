#include "POW_Block.h"

POW_Block::POW_Block(SDL_Renderer* renderer, LevelMap* map)
{
	this->renderer = renderer;
	this->levelMap = map;

	std::string imgPath = "images/PowBlock.png";
	texture = new Texture2D(renderer);
	texture->LoadFromFile(imgPath);
	singleSprite_w = texture->GetWidth() / 3;
	singleSprite_h = texture->GetHeight();
	numHitsRemaining = 3;
	position = Vector2D((SCREEN_WIDTH / 2) -  singleSprite_w / 2, 260);
}

POW_Block::~POW_Block()
{
	renderer = nullptr;
	delete texture;
	texture = nullptr;
	levelMap = nullptr;
}

void POW_Block::Render()
{
	if (numHitsRemaining > 0)
	{
		float left = singleSprite_w * (numHitsRemaining - 1);
		Box2D portionOfSprite = {left, 0, singleSprite_w, singleSprite_h};
		Box2D destination = {position.x, position.y, singleSprite_w, singleSprite_h};
		texture->Render(portionOfSprite, destination, SDL_FLIP_NONE, 0, false);
	}
}

Box2D POW_Block::GetCollisionBox()
{
	Box2D box;
	box.x = position.x;
	box.y = position.y;
	box.width = texture->GetWidth() / singleSprite_w;
	box.height = texture->GetHeight() / singleSprite_h;
	return box;
}

void POW_Block::TakeHit()
{
	numHitsRemaining--;
	if (numHitsRemaining <= 0)
	{
		levelMap->SetTile(int(position.x / TILE_WIDTH), int(position.y / TILE_HEIGHT), 0);
	}
}

bool POW_Block::isAvailable()
{
	return numHitsRemaining > 0;
}
