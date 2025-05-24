#include "ACE_Actor.h"



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

	if ((GetBoundingBox().y + GetBoundingBox().height) > 1080)
	{
		isGrounded = true;
		transform.position.y = 1080 - GetBoundingBox().height;
		velocity.y = 0.0f;
	}
	
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

void ACE_Actor::AddGravity(float deltaTime)
{
	if (!isGrounded)
	{
		acceleration.y += GRAVITY * mass;
	}
}

void ACE_Actor::Render(SDL_Renderer* renderer)
{
	SDL_FlipMode flip = velocity.x < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	spriteComponent->RenderSprite(flip);
}
