#include "ACE_Character.h"

#include "Objects/Managers/ACE_EventSystem.h"

ACE_Character::ACE_Character()
{
	spriteData = "Resources/Images/Mario.png";
}

ACE_Character::~ACE_Character()
{
}

void ACE_Character::Update(float deltaTime, SDL_Event event)
{
	ACE_Actor::Update(deltaTime, event);
	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
		switch (event.key.key)
		{
		case SDLK_SPACE:
			ACE_Event jumpEvent
			{
				.type = ACE_EventType::Custom,
				.data = this,
				.customType = "CharacterJump"
			};
			ACE_EventSystem::Instance()->Dispatch(jumpEvent);
			break;
		}
		break;
	}
}
