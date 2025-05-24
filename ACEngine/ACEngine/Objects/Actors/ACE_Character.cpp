#include "ACE_Character.h"

#include "Objects/Managers/ACE_EventSystem.h"

ACE_Character::ACE_Character()
{
	spriteData = "Resources/Images/Mario.png";
	healthComponent = new ACE_HealthComponent();
	components.push_back(healthComponent);
	mass = 100.0f;
}

void ACE_Character::Init()
{
	ACE_Actor::Init();
	ACE_EventSystem::Instance()->Subscribe(BindCustomCallback("CharacterDied")
	{
		if ((ACE_Character*)event.data == this)
		{
			OnDied(event);
		}
	});
}

void ACE_Character::Update(float deltaTime, SDL_Event event)
{
	ACE_Actor::Update(deltaTime, event);
}

void ACE_Character::Move(ACE_Vector2D direction, float deltaTime)
{
	velocity.x += direction.x * moveSpeed;
}

void ACE_Character::Jump(float JumpForce)
{
	if (isGrounded)
	{
		velocity.y -= JumpForce;
		isGrounded = false;
	}
}

void ACE_Character::OnDied(const ACE_Event& event)
{
	std::cout << "i died :(" << "\n";
}
