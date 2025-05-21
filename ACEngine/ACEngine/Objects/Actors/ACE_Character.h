#pragma once
#include "ACE_Actor.h"

class ACE_Character : public ACE_Actor
{
public:
	ACE_Character();
	~ACE_Character();
	void Update(float deltaTime, SDL_Event event) override;
};
