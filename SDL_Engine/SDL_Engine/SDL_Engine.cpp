#include <SDL3/SDL.h>
#include <iostream>
#include "ACE_WindowManager.h"

bool Update();

int main(int argc, char* argv[])
{
    ACE_WindowManager* windowManager = new ACE_WindowManager();
    windowManager->CreateWindow();
    
    SDL_Texture* background_texture = windowManager->LoadTextureFromFile("images/test.bmp");
        
    // Main loop
    bool bIsGameRunning = true;
    while (bIsGameRunning)
    {
        intBox2D RenderBox = windowManager->GetWindowSize();
        windowManager->Render(background_texture, RenderBox);
        bIsGameRunning = Update();
    }
    windowManager->FreeTexture(background_texture);
    windowManager->CloseWindow();

    delete windowManager;
    return 0;
}

bool Update()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch (event.type)
    {
    case SDL_EVENT_QUIT:
        return false;
        break;
    case SDL_EVENT_KEY_DOWN:
        switch (event.key.key)
        {
            case SDLK_ESCAPE:
                return false;
                break;
        }
        break;
    }
    return true;
}
