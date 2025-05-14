#include "Character_Luigi.h"

Character_Luigi::Character_Luigi(SDL_Renderer* renderer, std::string imgPath, Vector2D initPosition, LevelMap* map) : Character(renderer, imgPath, initPosition, map){}

void Character_Luigi::Update(float deltaTime, SDL_Event* event)
{
	Character::Update(deltaTime, event);

	switch (event->type)
	{
	case SDL_EVENT_KEY_DOWN: // key down events
		switch (event->key.key)
		{
	case SDLK_W:
			if (canJump)
			{
				Jump();
			}
			break;
	case SDLK_D:
			isMovingRight = true;
			break;
	case SDLK_S:
			break;
	case SDLK_A:
			isMovingLeft = true;
			break;
	default:
			break;
		}
		break;
	case SDL_EVENT_KEY_UP: // key up events
		switch (event->key.key)
		{
	case SDLK_W:
			break;
	case SDLK_D:
			isMovingRight = false;
			break;
	case SDLK_S:
			break;
	case SDLK_A:
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
