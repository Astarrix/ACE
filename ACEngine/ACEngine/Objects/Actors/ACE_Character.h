#pragma once
#include "ACE_Actor.h"
#include "Objects/Components/Sub-Components/ACE_HealthComponent.h"
#include "Objects/Managers/ACE_EventSystem.h"

class ACE_Character : public ACE_Actor
{
public:
	ACE_Character();
	void Init() override;
	void Update(float deltaTime, SDL_Event event) override;
	void Move(ACE_Vector2D direction, float deltaTime);
	void Jump(float JumpForce = 1000.0f);
protected:
	void OnDied(const ACE_Event& event);
	float moveSpeed = 300.0f;
	ACE_Vector2D moveDirection;
	
private:
	ACE_HealthComponent* healthComponent;
};
