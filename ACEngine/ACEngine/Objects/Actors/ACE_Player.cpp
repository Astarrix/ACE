#include "ACE_Player.h"

#include "Objects/Managers/ACE_WindowManager.h"

ACE_Player::ACE_Player()
{
	spriteData = SpriteData("Resources/images/Mario.png", 1, 1);
	friendlyName = "Player";
	textRenderer = new ACE_TextRenderer(ACE_WindowManager::Instance()->GetRenderer());
	textRenderer->LoadFontToText("Resources/Fonts/JetBrainsMono.ttf", 16);
	textRenderer->SetText("Player 1");
	textRenderer->SetTextOffset(-20, -20);
	textRenderer->SetTextStyle(TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
	AddComponent(textRenderer);
}

void ACE_Player::OnHit(const HitData& hitData)
{
	ACE_Character::OnHit(hitData);
	std::cout << "Player Hit " << hitData.body1->friendlyName << std::endl;
}

void ACE_Player::Update(float deltaTime, SDL_Event event)
{
	ACE_Character::Update(deltaTime, event);
	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
		switch (event.key.key)
		{
		case SDLK_SPACE:
		case SDLK_UP:
			Jump(500);
			break;
		case SDLK_A:
		case SDLK_LEFT:
			isMovingLeft = true;
			break;
		case SDLK_D:
		case SDLK_RIGHT:
			isMovingRight = true;
			break;
		}
		break;
	case SDL_EVENT_KEY_UP:
		switch (event.key.key)
		{
		case SDLK_A:
		case SDLK_LEFT:
			isMovingLeft = false;
			break;
		case SDLK_D:
		case SDLK_RIGHT:
			isMovingRight = false;
			break;
		}
		break;
	}
	moveDirection.x = isMovingRight ? 1.0f : isMovingLeft ? -1.0f : 0.0f;
	if (moveDirection.x > 0 || moveDirection.x < 0) { Move(moveDirection); }
}

void ACE_Player::Render(SDL_Renderer* renderer)
{
	ACE_Character::Render(renderer);
	textRenderer->RenderText(GetPosition().x, GetPosition().y);
}
