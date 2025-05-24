#include "ACE_HealthComponent.h"

#include <iostream>
#include <ostream>

#include "Objects/Managers/ACE_EventSystem.h"

void ACE_HealthComponent::Heal(float healthGain)
{
	health = std::clamp(health + healthGain, 0.0f, maxHealth);
	ACE_EventSystem::Instance()->Dispatch(OnHealed);
}

void ACE_HealthComponent::TakeDamage(float healthLost)
{
	health = std::clamp(health - healthLost, 0.0f, maxHealth);
	if (health <= 0.0f)
	{
		ACE_Event OnDied{ACE_EventType::Custom, parent, "CharacterDied"};
		ACE_EventSystem::Instance()->Dispatch(OnDied);
	}
}


