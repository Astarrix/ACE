#pragma once
#include <vector>

#include "Commons/ACE_Transform2D.h"
#include "Objects/ACE_Object.h"
#include "Objects/Components/Sub-Components/ACE_Sprite2D.h"
#include "Objects/Components/Sub-Components/ACE_Texture2D.h"
#include "SDL3/SDL_render.h"


class ACE_Actor : public ACE_Object
{
public:
	ACE_Actor(const char* spritePath = nullptr);
	~ACE_Actor() override;
	
	void Init() override;
	void Update(float deltaTime, SDL_Event event) override;
	void Render(SDL_Renderer* renderer);

	ACE_Transform2D GetTransform() const {return transform;}
	void SetTransform(const ACE_Transform2D& inTransform) {this->transform = inTransform;}
protected:
	ACE_Transform2D transform;
	SpriteData spriteData = nullptr;
	std::vector<ACE_Component*> components;
private:
	void InitComponents();
	void UpdateComponents(float deltaTime, SDL_Event event);
	
	ACE_Sprite2D* spriteComponent = nullptr;
};
