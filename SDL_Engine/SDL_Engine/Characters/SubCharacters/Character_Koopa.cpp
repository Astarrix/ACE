#include "Character_Koopa.h"

#include "Components/ACE_Animator.h"

Character_Koopa::Character_Koopa(SDL_Renderer* renderer, SpriteData spriteData, ACE_Vector2D initPosition, ACE_LevelMap* map,
                                 FACING_DIRECTION startDirection, float MovementSpeed) : Character(renderer, spriteData, initPosition, map)
{
	facingDirection = startDirection;
	this->MovementSpeed = MovementSpeed;
	position = initPosition;
	injured	= false;
}

Character_Koopa::~Character_Koopa()
{
	Character::~Character();
}


void Character_Koopa::Render()
{
	Character::Render();
}

void Character_Koopa::Update(float deltaTime, SDL_Event* event)
{
	Character::Update(deltaTime, event);
	if (!injured)
	{
		if (position.y < 300.0f && (position.x < 0 || position.x >= SCREEN_WIDTH - sprite->GetSpriteWidth())) // bounce if on above floor wall
		{
			facingDirection = facingDirection == FACING_RIGHT ? FACING_LEFT : FACING_RIGHT;
		}
		if (facingDirection == FACING_RIGHT)
		{
			isMovingRight = true;
			isMovingLeft = false;
		}
		else if (facingDirection == FACING_LEFT)
		{
			isMovingRight = false;
			isMovingLeft = true;
		}
	}
	else
	{
		isMovingRight = false;
		isMovingLeft = false;
		injuredTime -= deltaTime;
		if (injuredTime <= 0)
		{
			FlipRightWayUp();
		}
	}
}

void Character_Koopa::Jump(float inJumpForce)
{
	Character::Jump(100.0f);
}

void Character_Koopa::TakeDamage()
{
	sprite->SetSpriteIndex(1);
	injured = true;
	injuredTime = 2.5f;
	Jump();
}

void Character_Koopa::FlipRightWayUp()
{
	sprite->SetSpriteIndex(0);
	facingDirection = facingDirection == FACING_RIGHT ? FACING_LEFT : FACING_RIGHT;
	injured = false;
	Jump();
}
