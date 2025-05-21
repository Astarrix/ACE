#include "ACE_Actor.h"

#include "Objects/Managers/ACE_WindowManager.h"

ACE_Actor::ACE_Actor(const char* spritePath)
{
	if (spritePath != nullptr)
	{
		spriteData = spritePath;
	}
}

ACE_Actor::~ACE_Actor()
{
	for (ACE_Component* component : components)
	{
		delete component;
		component = nullptr;
	}
}

void ACE_Actor::Update(float deltaTime, SDL_Event event)
{
	ACE_Object::Update(deltaTime, event);;
	for (ACE_Component* component : this->components)
	{
		component->Update(deltaTime, event);
	}
}

void ACE_Actor::Init()
{
	ACE_Object::Init();
	if (spriteData.path != nullptr)
	{
		InitComponents();
	} else
	{
		std::cout << "ACTOR HAS NO IMAGE PATH ATTACHED" << "\n";
	}
}

void ACE_Actor::InitComponents()
{
	spriteComponent = new ACE_Sprite2D();
	spriteComponent->LoadSpriteSheetFromFile(ACE_WindowManager::Instance()->GetRenderer(), spriteData);
	components.push_back(spriteComponent);
	for (ACE_Component* component : this->components)
	{
		component->Init(this);
	}
}

void ACE_Actor::UpdateComponents(float deltaTime, SDL_Event event)
{
	for (ACE_Component* component : this->components)
	{
		component->Update(deltaTime, event);
	}
}

void ACE_Actor::Render(SDL_Renderer* renderer)
{
	spriteComponent->RenderSprite();
}
