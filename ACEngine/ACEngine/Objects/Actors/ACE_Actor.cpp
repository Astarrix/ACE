#include "ACE_Actor.h"

#include <algorithm>

#include "Commons/ACE_Constants.h"
#include "Objects/Managers/ACE_CollisionManager.h"
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
	ACE_Object::Update(deltaTime, event);
	SolveMovement(deltaTime);
	
	if ((GetBoundingBox().y + GetBoundingBox().height) > ACE_WindowManager::Instance()->GetWindowSize().y)
	{
		isGrounded = true;
		transform.position.y = ACE_WindowManager::Instance()->GetWindowSize().y - GetBoundingBox().height;
		velocity.y = 0.0f;
	}

	ACE_CollisionManager::getInstance()->CheckAllCollisions();
	UpdateComponents(deltaTime, event);
}

void ACE_Actor::Init()
{
	ACE_Object::Init();
	if (spriteData.path != nullptr)
	{
		InitComponents();
	}
	else
	{
		std::cout << "ACTOR HAS NO IMAGE PATH ATTACHED" << "\n";
	}
	
	ACE_EventSystem::Instance()->Subscribe(ACE_EventType::Collision, [this](const ACE_Event& event)
	{
		const HitData hitinfo = *(HitData*)event.dataBuffer_1; // make a dereferenced copy to pass through (safe)
		if (hitinfo.body1 == this || hitinfo.body2 == this)
		{
			OnHit(hitinfo);
		}
	});
}

void ACE_Actor::OnHit(const HitData& hitData)
{
}

void ACE_Actor::InitComponents()
{
	spriteComponent = new ACE_Sprite2D();
	AddComponent(spriteComponent);
	spriteComponent->LoadSpriteSheetFromFile(ACE_WindowManager::Instance()->GetRenderer(), spriteData);
}

void ACE_Actor::UpdateComponents(float deltaTime, SDL_Event event)
{
	for (ACE_Component* component : this->components)
	{
		component->Update(deltaTime, event);
	}
}

void ACE_Actor::AddGravity(float deltaTime)
{
		acceleration.y += GRAVITY * mass;
}

void ACE_Actor::SolveMovement(float deltaTime)
{
	if (hasGravity)
	{
		AddGravity(deltaTime);
	}

	float currentDrag = isGrounded ? groundDragCoefficient : skyDragCoefficient;
	
	velocity += acceleration * deltaTime;
	
	if (maxVelocity.x > 0)
	{
		velocity.x = std::clamp(velocity.x, -maxVelocity.x, maxVelocity.x);
	}
	if (maxVelocity.y > 0)
	{
		velocity.y = std::clamp(velocity.y, -maxVelocity.y, maxVelocity.y);
	}
	velocity.x *= currentDrag;
	transform.position += velocity * deltaTime;
	acceleration = 0.0f;

}

void ACE_Actor::Render(SDL_Renderer* renderer)
{
	SDL_FlipMode flip = velocity.x < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	spriteComponent->RenderSprite(flip);
}

void ACE_Actor::AddComponent(ACE_Component* component)
{
	components.push_back(component);
	component->Init(this);
}
