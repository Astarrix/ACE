#pragma once

#include "Commons/ACE_Vector2D.h"
#include "Objects/Actors/ACE_Actor.h"
#include "Objects/Components/Sub-Components/ACE_HealthComponent.h"

class ACE_Character : public ACE_Actor
{
public:
	ACE_Character();
	void Init() override;
	void Update(float deltaTime, SDL_Event event) override;
	void Move(ACE_Vector2D direction);
	void Jump(float JumpForce = 1000.0f);
	
protected:
	float moveSpeed = 175.0f;
	ACE_Vector2D moveDirection;
	
private:
	ACE_HealthComponent* healthComponent;
	void OnDied(const ACE_Event& event);
};
