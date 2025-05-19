#pragma once
#include "Characters/Character.h"

class Character_Koopa : public Character
{
public:
	Character_Koopa(SDL_Renderer* renderer, SpriteData spriteData, ACE_Vector2D initPosition = ACE_Vector2D(0.0, 0.0), ACE_LevelMap* map = nullptr, FACING_DIRECTION startDirection = FACING_RIGHT, float MovementSpeed = 20.0f);
	~Character_Koopa() override;
	void Render() override;
	void Update(float deltaTime, SDL_Event* event) override;
	bool IsInjured() {return injured;}
	void TakeDamage();
private:
	bool injured;
	float injuredTime;

	void Jump(float inJumpForce = 100.0f) override;


	void FlipRightWayUp();
	
};
