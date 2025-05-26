#pragma once
#include <vector>

#include "Objects/ACE_Object.h"
#include "Commons/ACE_Box2D.h"
#include "Commons/ACE_Transform2D.h"
#include "SDL3/SDL_render.h"
#include "Objects/Components/Sub-Components/ACE_Sprite2D.h"
#include "Objects/Managers/ACE_CollisionManager.h"

class ACE_Actor : public ACE_Object
{
public:
	ACE_Actor(const char* spritePath = nullptr);
	~ACE_Actor() override;

	void Init() override;
	void Update(float deltaTime, SDL_Event event) override;
	virtual void Render(SDL_Renderer* renderer);
	void AddComponent(ACE_Component* component);
	
	bool generateHitEvents = true;
	bool hasCollision = true;
	bool isStaticMove = false;

	void SetTransform(const ACE_Transform2D& inTransform) { this->transform = inTransform; }
	void SetVelocity(const ACE_Vector2D& inVelocity) { this->velocity = inVelocity; }
	void SetPosition(const ACE_Vector2D& inPosition) { this->transform.position = inPosition; }
	void SetScale(const ACE_Vector2D& inScale) { this->transform.scale = inScale; }
	void SetAngle(const float& inAngle) { this->transform.angle = inAngle; }
	void SetIsGrounded(const bool& inGrounded) {this->isGrounded = inGrounded; }

	ACE_Transform2D GetTransform() const { return transform; }
	ACE_Vector2D GetPosition() const { return transform.position; }
	ACE_Vector2D GetScale() const { return transform.scale; }
	ACE_Vector2D GetVelocity() const { return velocity; }
	ACE_Box2D GetBoundingBox() const
	{
		return {
			transform.position.x, transform.position.y, spriteComponent->GetSpriteWidth() * transform.scale.x,
			spriteComponent->GetSpriteHeight() * transform.scale.y,
		};
	}
	float GetAngle() const { return transform.angle; }
	bool IsGrounded() const { return isGrounded; }
	
	virtual void OnHit(const HitData& hitData);
protected:
	/* PARAMETERS */
	
	float mass = 20.0f;
	bool hasGravity = true;
	float skyDragCoefficient = 0.9999f;
	float groundDragCoefficient = 0.995f;
	ACE_Vector2D maxVelocity = {300,-1};


	ACE_Sprite2D* spriteComponent = nullptr;
	SpriteData spriteData = nullptr;
	std::vector<ACE_Component*> components;
	

private:
	void InitComponents();
	void UpdateComponents(float deltaTime, SDL_Event event);
	virtual void AddGravity(float deltaTime);
	void SolveMovement(float deltaTime);
	ACE_Transform2D transform;
	ACE_Vector2D velocity = {0,0};
	ACE_Vector2D acceleration = {0,0};
	bool isGrounded = false;
};
