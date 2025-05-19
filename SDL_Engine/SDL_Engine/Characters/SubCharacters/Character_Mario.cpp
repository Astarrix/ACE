#include "Character_Mario.h"

Character_Mario::Character_Mario(SDL_Renderer* renderer, SpriteData spriteData, ACE_Vector2D initPosition, ACE_LevelMap* map) : Character(renderer, spriteData, initPosition, map){}

void Character_Mario::Update(float deltaTime, SDL_Event* event)
{
	Character::Update(deltaTime, event);

	switch (event->type)
	{
	case SDL_EVENT_KEY_DOWN: // key down events
		switch (event->key.key)
		{
	case SDLK_UP:
			if (canJump)
			{
				Jump();
			}
			break;
	case SDLK_RIGHT:
			isMovingRight = true;
			break;
	case SDLK_DOWN:
			break;
	case SDLK_LEFT:
			isMovingLeft = true;
			break;
	default:
			break;
		}
		break;
	case SDL_EVENT_KEY_UP: // key up events
		switch (event->key.key)
		{
	case SDLK_UP:
			break;
	case SDLK_RIGHT:
			isMovingRight = false;
			break;
	case SDLK_DOWN:
			break;
	case SDLK_LEFT:
			isMovingLeft = false;
			break;
	default:
			break;
		}
		break;
	default:
		break;
	}
}
