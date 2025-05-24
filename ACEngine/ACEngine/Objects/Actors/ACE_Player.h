#pragma once
#include "ACE_Character.h"

class ACE_Player : public ACE_Character
{
public:
	ACE_Player();
	void Update(float deltaTime, SDL_Event event) override;
private:
	
	bool isMovingLeft = false;
	bool isMovingRight = false;
};
