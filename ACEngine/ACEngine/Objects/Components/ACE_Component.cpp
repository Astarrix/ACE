#include "ACE_Component.h"

ACE_Component::~ACE_Component()
{
}

void ACE_Component::Update(float deltaTime, SDL_Event event)
{
	ACE_Object::Update(deltaTime, event);
}

void ACE_Component::Init(ACE_Actor* inParent)
{
	ACE_Object::Init();
	this->parent = inParent;
}
