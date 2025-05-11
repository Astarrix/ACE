#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    renderer = nullptr;
}

GameScreen::~GameScreen()
{
    this->renderer = nullptr;
}