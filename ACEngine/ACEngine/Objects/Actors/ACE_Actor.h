#pragma once
#include <algorithm>
#include <ranges>
#include <vector>

#include "Commons/ACE_Box2D.h"
#include "Commons/ACE_Transform2D.h"
#include "Objects/ACE_Object.h"
#include "SDL3/SDL_render.h"
#include "Commons/ACE_Constants.h"
#include "Objects/Components/Sub-Components/ACE_Sprite2D.h"
#include "Objects/Managers/ACE_WindowManager.h"
#include "Objects/Components/Sub-Components/ACE_Sprite2D.h"

class ACE_Actor : public ACE_Object
{
protected:
	ACE_Sprite2D* spriteComponent = nullptr;
	SpriteData spriteData = nullptr;
	std::vector<ACE_Component*> components;
	
	
public:
	ACE_Actor(const char* spritePath = nullptr);
	~ACE_Actor() override;

	void Init() override;
	void Update(float deltaTime, SDL_Event event) override;
	void Render(SDL_Renderer* renderer);

	ACE_Transform2D GetTransform() const { return transform; }
	ACE_Box2D GetBoundingBox() const
	{
		return {
			transform.position.x, transform.position.y, spriteComponent->GetSpriteWidth() * transform.scale.x,
			spriteComponent->GetSpriteHeight() * transform.scale.y,
		};
	}

	void SetTransform(const ACE_Transform2D& inTransform) { this->transform = inTransform; }

protected:
	ACE_Transform2D transform;
	float mass = 20.0f;
	bool hasGravity = true;
	ACE_Vector2D velocity = {0,0};
	ACE_Vector2D acceleration = {0,0};
	ACE_Vector2D maxVelocity = {300,-1};
	float skyDragCoefficient = 0.9999f;
	float groundDragCoefficient = 0.995f;
	
	bool isGrounded = false;

private:
	void InitComponents();
	void UpdateComponents(float deltaTime, SDL_Event event);
	virtual void AddGravity(float deltaTime);

};
