#include "GameScreen.h"

#include "commons/constants.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    renderer = nullptr;
    screenshake = false;
    shakeTime = 0.0f;
    wobble = 0.0f;
    backgroundYPos = 0.0f;
}

GameScreen::~GameScreen()
{
    this->renderer = nullptr;
}

void GameScreen::Update(float deltaTime, SDL_Event* event)
{
    if (screenshake)
    {
        shakeTime -= deltaTime;
        wobble++;
        backgroundYPos = sin(wobble);
        backgroundYPos *= 3.0f;
        if (shakeTime <= 0.0f)
        {
            shakeTime = false;
            backgroundYPos = 0.0f;
        }
    }
}

void GameScreen::DoScreenShake()
{
    screenshake = true;
    shakeTime = SHAKE_DURATION;
    wobble = 0.0f;
}
