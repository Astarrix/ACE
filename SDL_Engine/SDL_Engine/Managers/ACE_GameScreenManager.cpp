#include "ACE_GameScreenManager.h"
#include "Screens/GameScreen.h"
#include "Screens/SubScreens/GameScreen_L1.h"
#include "Screens/SubScreens/GameScreen_L2.h"
#include "SDL3/SDL.h"

ACE_GameScreenManager::ACE_GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
    this->renderer = renderer;
    renderer = nullptr;
    currentScreen = nullptr;
    ChangeScreen(startScreen);
}

ACE_GameScreenManager::~ACE_GameScreenManager()
{
    renderer = nullptr;
    delete currentScreen;
    currentScreen = nullptr;
}

void ACE_GameScreenManager::Render()
{
    currentScreen->Render();
}

void ACE_GameScreenManager::Update(float deltaTime, SDL_Event* event)
{
    currentScreen->Update(deltaTime, event);
}

void ACE_GameScreenManager::ChangeScreen(SCREENS screen)
{
    if (currentScreen != nullptr)
    {
        delete currentScreen;
    }
    GameScreen_L1* tempScreen;
    GameScreen_L2* tempScreen2;
    switch (screen)
    {
        case SCREEN_LEVEL1:
            tempScreen = new GameScreen_L1(renderer);
            currentScreen = (GameScreen*)tempScreen;
            tempScreen = nullptr;
            break;
        case SCREEN_LEVEL2:
            tempScreen2 = new GameScreen_L2(renderer);
            currentScreen = (GameScreen*)tempScreen2;
            tempScreen2 = nullptr;
        default:
            break;
    }
}