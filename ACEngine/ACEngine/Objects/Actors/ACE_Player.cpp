#include "ACE_Player.h"

ACE_Player::ACE_Player()
{
	spriteData = SpriteData("Resources/images/Goomba.png", 2, 1);
	transform.scale.x = 2;
	transform.scale.y = 2;
	friendlyName = "Player";
}

void ACE_Player::Update(float deltaTime, SDL_Event event)
{
	ACE_Character::Update(deltaTime, event);
	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
		switch (event.key.key)
		{
		case SDLK_SPACE:
		case SDLK_UP:
			Jump(750);
			break;
		case SDLK_A:
		case SDLK_LEFT:
			isMovingLeft = true;
			break;
		case SDLK_D:
		case SDLK_RIGHT:
			isMovingRight = true;
			break;
		}
		break;
	case SDL_EVENT_KEY_UP:
		switch (event.key.key)
		{
		case SDLK_A:
		case SDLK_LEFT:
			isMovingLeft = false;
			break;
		case SDLK_D:
		case SDLK_RIGHT:
			isMovingRight = false;
			break;
		}
		break;
	}
	moveDirection.x = isMovingRight ? 1.0f : isMovingLeft ? -1.0f : 0.0f;
	if (moveDirection.x > 0 || moveDirection.x < 0) { Move(moveDirection, deltaTime); }
}
