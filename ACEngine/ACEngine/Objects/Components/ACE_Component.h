#pragma once
#include "Objects/ACE_Object.h"

class ACE_Actor;

class ACE_Component : public ACE_Object
{
public:
	ACE_Component() = default;
	~ACE_Component() override;
	void Update(float deltaTime, SDL_Event event) override;
	void Init(ACE_Actor* inParent);
protected:
	ACE_Actor* parent = nullptr;
};
