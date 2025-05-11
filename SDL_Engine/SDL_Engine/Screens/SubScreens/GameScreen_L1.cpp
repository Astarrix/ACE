#include "GameScreen_L1.h"
#include "Texture2D.h"

GameScreen_L1::GameScreen_L1(SDL_Renderer* renderer) : GameScreen(renderer)
{
    SetUpLevel();
}

GameScreen_L1::~GameScreen_L1()
{
    delete background_texture;
    background_texture = nullptr;
}

void GameScreen_L1::Render()
{
    GameScreen::Render();
    background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreen_L1::Update(float deltaTime, SDL_Event* event)
{
    GameScreen::Update(deltaTime, event);
}

bool GameScreen_L1::SetUpLevel()
{
    background_texture = new Texture2D(renderer);
    if (!background_texture->LoadFromFile("images/test.bmp"))
    {
        std::cout << "Unable to load background texture" << std::endl;
        return false;       
    }
    return true;
}
