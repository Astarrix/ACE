#pragma once
#include "SDL3/SDL_events.h"

class ACE_Object
{
public:
	ACE_Object() = default;
	virtual ~ACE_Object() = default;
	virtual void Init();
	virtual void Update(float deltaTime, SDL_Event event);
private:
};
