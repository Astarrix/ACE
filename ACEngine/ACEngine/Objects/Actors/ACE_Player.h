#pragma once
#include "ACE_Character.h"
#include "Objects/Components/Sub-Components/ACE_TextRenderer.h"

class ACE_Player : public ACE_Character
{
public:
	ACE_Player();
	void OnHit(const HitData& hitData) override;
	void Update(float deltaTime, SDL_Event event) override;
	void Render(SDL_Renderer* renderer) override;
private:
	ACE_TextRenderer* textRenderer = nullptr;;
	bool isMovingLeft = false;
	bool isMovingRight = false;
};
