#include "POW_Block.h"

#include "Managers/ACE_AudioManager.h"

POW_Block::POW_Block(SDL_Renderer* renderer, ACE_LevelMap* map)
{
	this->renderer = renderer;
	this->levelMap = map;
	numHitsRemaining = 3;
	std::string imgPath = "images/PowBlock.png";
	sprite = new ACE_Sprite2D(renderer);
	sprite->LoadSpriteSheetFromFile(SpriteData(imgPath, 1, 3));
	sprite->SetSpriteIndex(numHitsRemaining - 1);
	singleSprite_w = sprite->GetWidth() / 3;
	singleSprite_h = sprite->GetHeight() / 1;

	position = ACE_Vector2D((SCREEN_WIDTH / 2) -  sprite->GetSpriteWidth() / 2, 260);
}

POW_Block::~POW_Block()
{
	renderer = nullptr;
	delete sprite;
	sprite = nullptr;
	levelMap = nullptr;
}

void POW_Block::Render()
{
	if (numHitsRemaining > 0)
	{
		sprite->RenderSprite(position);
	}
}

ACE_Box2D POW_Block::GetCollisionBox()
{
	ACE_Box2D box;
	box.x = position.x;
	box.y = position.y;
	box.width = sprite->GetSpriteWidth();
	box.height = sprite->GetSpriteHeight();
	return box;
}

void POW_Block::TakeHit()
{
	std::cout << "Hit" << std::endl;
	ACE_AudioManager::Instance()->LoadWav("audio/Sounds/smb_bump.wav");
	numHitsRemaining--;
	if (numHitsRemaining <= 0)
	{
		levelMap->SetTile(int(position.x / TILE_WIDTH), int(position.y / TILE_HEIGHT), 0);

	}
	sprite->SetSpriteIndex(numHitsRemaining - 1);
}

bool POW_Block::isAvailable()
{
	return numHitsRemaining > 0;
}
