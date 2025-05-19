#pragma once
#include <functional>
#include <map>

#include "Commons/ACE_Box2D.h"
#include "SDL3/SDL_events.h"


class ACE_EventManager
{
	typedef Uint32 eventID;
	typedef int assignedID;
public:
	enum ACE_EVENTS
	{
		ACE_EVENT_COLLISION,
		ACE_EVENT_DEATH,
		ACE_EVENT_EMPTY
	};
	ACE_EventManager();
	~ACE_EventManager();
	void PollEvents(SDL_Event* event);
	Uint32 GetEventLabel(ACE_EVENTS event);
private:
	Uint32 numEvents = 3; // NEEDS TO BE THE SAME NUMBER AS THE NUMBER OF ENTRIES IN ACE_EVENTS
	std::map<eventID, assignedID> eventIDs;
	void PopulateEventIDs();
	bool IsOfEventType(SDL_Event* event, ACE_EVENTS eventType) {return event->user.type == Uint32(eventIDs[eventType]);}

};
