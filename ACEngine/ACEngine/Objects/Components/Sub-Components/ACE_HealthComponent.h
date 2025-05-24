#pragma once
#include <algorithm>
#include "Objects/Components/ACE_Component.h"
#include "Objects/Managers/ACE_EventSystem.h"

class ACE_HealthComponent : public ACE_Component
{
public:
	void Heal(float healthGain);
	void TakeDamage(float healthLost);
	float GetHealth() const { return health; }
	float GetMaxHealth() const { return maxHealth; }
	void SetMaxHealth(float newMaxHealth) { maxHealth = newMaxHealth; }
	
private:
	float maxHealth = 100.0f;
	float health = maxHealth;

	ACE_Event OnHealed{ACE_EventType::Custom, parent, "CharacterHealed"};
	
	
};