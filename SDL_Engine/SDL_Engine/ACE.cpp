#include <SDL3/SDL.h>
#include <iostream>
#include "Managers/ACE_WindowManager.h"
#include "Managers/GameScreenManager.h"

bool Update();
void Render();
void Close();

GameScreenManager* gameScreenManager;
ACE_WindowManager* windowManager;
Uint32 gOldTime;

int main(int argc, char* argv[])
{
    windowManager = new ACE_WindowManager();
    windowManager->CreateWindow();
    gameScreenManager = new GameScreenManager(windowManager->GetRenderer(), SCREEN_LEVEL1);
    gOldTime = SDL_GetTicks();
    
        
    // Main loop
    bool bIsGameRunning = true;
    while (bIsGameRunning)
    {
        Render();
        bIsGameRunning = Update();
    }
    Close();
    return 0;
}

bool Update()
{
    Uint32 NewTime = SDL_GetTicks();
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch (event.type) // game events
    {
    case SDL_EVENT_QUIT:
        return false;
        break;
    case SDL_EVENT_KEY_DOWN:
        switch (event.key.key) // keyboard events
        {
            case SDLK_ESCAPE:
                return false;
                break;
            case SDLK_SPACE:
                gameScreenManager->ChangeScreen(SCREEN_LEVEL2);
                windowManager->SetWindowTitle("ACE - Level 2");
                windowManager->SetWindowSize(1280, 720);
                break;
        }
        break;
    }
    gameScreenManager->Update((NewTime - gOldTime) / 1000.0f, &event);
    gOldTime = NewTime;
    return true;
}

void Render()
{

    SDL_SetRenderDrawColor(windowManager->GetRenderer(), 0XFF, 0XFF, 0XFF, 0XFF);
    SDL_SetRenderDrawBlendMode(windowManager->GetRenderer(), SDL_BLENDMODE_NONE);
    SDL_RenderClear(windowManager->GetRenderer());
    gameScreenManager->Render();
    SDL_RenderPresent(windowManager->GetRenderer());
}

void Close()
{
    delete gameScreenManager;
    gameScreenManager = nullptr;
    windowManager->CloseWindow();
    delete windowManager;
}