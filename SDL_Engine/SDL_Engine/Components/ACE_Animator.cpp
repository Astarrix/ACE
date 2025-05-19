#include "ACE_Animator.h"

ACE_Animator::ACE_Animator(ACE_Sprite2D* sprite, int startFrame, int endFrame, float frameRate)
{
	this->sprite = sprite;
	this->startFrame = startFrame;
	this->endFrame = endFrame;
	this->frameRate = frameRate;
	this->currentFrame = startFrame;
}

void ACE_Animator::Update(float deltaTime)
{
	if (isPlaying)
	{
		startTime += deltaTime;
		frameTime += deltaTime;
		if (frameTime >= frameRate)
		{
			frameTime = 0.0f;
			currentFrame++;
			if (currentFrame + startFrame > endFrame)
			{
				if (isLooping)
				{
					currentFrame = 0;
				}
				else
				{
					End();
				}
			}
			sprite->SetSpriteIndex(currentFrame + startFrame);
		}
	}
}

void ACE_Animator::Render(ACE_Vector2D position, SDL_FlipMode flip)
{
	sprite->RenderSprite(position, flip);
}

void ACE_Animator::Begin(bool isLooping)
{
	if (!sprite->IsInitialised()) { return; }
	startTime = 0.0f;
	frameTime = 0.0f;
	currentFrame = 0;
	this->isLooping = isLooping;
	isPlaying = true;
}

void ACE_Animator::End()
{
	isPlaying = false;
	startTime = 0.0f;
	frameTime = 0.0f;
}
