#include "ACE_EventManager.h"

#include <iostream>
#include <ostream>
#include "Managers/ACE_WindowManager.h"

ACE_EventManager::ACE_EventManager()
{
	PopulateEventIDs();
}

ACE_EventManager::~ACE_EventManager()
{
	eventIDs.clear();
}

void ACE_EventManager::PopulateEventIDs()
{
	Uint32 StartingEventID = SDL_RegisterEvents(numEvents);
	for (Uint32 i = 0; i < numEvents; i++)
	{
		eventIDs.insert(std::make_pair(i, StartingEventID + i));
		std::cout << "Event ID: " << eventIDs[i] << std::endl;
	}
}
void ACE_EventManager::PollEvents(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_EVENT_USER:
		if (IsOfEventType(event, ACE_EVENT_COLLISION))
		{
			std::cout << "Collision" << std::endl;
			ACE_WindowManager* window = (ACE_WindowManager*)event->user.data1;
			std::cout << window->GetWindowSize().width << std::endl;
		}
		else if (IsOfEventType(event, ACE_EVENT_DEATH))
		{
			
		}
		break;
	}
}

Uint32 ACE_EventManager::GetEventLabel(ACE_EVENTS event)
{
	return eventIDs[event];
}