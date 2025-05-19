#pragma once
#include "ACE_Sprite2D.h"

class ACE_Animator
{
public:
	ACE_Animator(ACE_Sprite2D* sprite, int startFrame, int endFrame, float frameRate);
	void Update(float deltaTime);
	void Render(ACE_Vector2D position, SDL_FlipMode flip);
	void Begin(bool isLooping);
	void End();

	ACE_Sprite2D* sprite;
	int currentFrame;
private:
	int startFrame;
	int endFrame;
	float frameRate;
	float startTime = 0.0f;
	float frameTime = 0.0f;
	bool isPlaying = false;
	bool isLooping = false;
};
