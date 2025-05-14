#include "GameScreen_L2.h"
#include "commons/Texture2D.h"

GameScreen_L2::GameScreen_L2(SDL_Renderer* renderer) : GameScreen(renderer)
{
    SetUpLevel();
}

GameScreen_L2::~GameScreen_L2()
{
    delete background_texture;
    background_texture = nullptr;
}

void GameScreen_L2::Render()
{
    GameScreen::Render();
    background_texture->Render(Vector2D(), SDL_FLIP_NONE);   
}

void GameScreen_L2::Update(float deltaTime, SDL_Event* event)
{
    GameScreen::Update(deltaTime, event);
}

bool GameScreen_L2::SetUpLevel()
{
    background_texture = new Texture2D(renderer);
    if (!background_texture->LoadFromFile("images/test_2.bmp"))
    {
        std::cout << "Unable to load background texture" << std::endl;
        return false;       
    }
    return true;
}
