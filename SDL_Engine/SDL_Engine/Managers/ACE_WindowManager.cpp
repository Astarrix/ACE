#include "ACE_WindowManager.h"

bool ACE_WindowManager::CreateWindow()
{
    if (!SDL_CreateWindowAndRenderer(
        "SDL Test Window",                  // Window title
        INIT_SCREEN_WIDTH,                       // Width
        INIT_SCREEN_HEIGHT,                      // Height
        SDL_WINDOW_RESIZABLE,              // Window flags
        &gameWindow,
        &gameRenderer))
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit(); //force exit the program
        return false;
    }
    return true;
}

void ACE_WindowManager::CloseWindow()
{
    // Clean up
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);
    gameRenderer = nullptr;
    gameWindow = nullptr;
    
    SDL_Quit();
}

ACE_Box2D ACE_WindowManager::GetWindowSize()
{
    int w,h;
    SDL_GetWindowSize(gameWindow, &w, &h);
    ACE_Box2D size = {0,0,float(w),float(h)};
    return size;
}

void ACE_WindowManager::SetWindowTitle(const char* title)
{
    SDL_SetWindowTitle(gameWindow, title);
}

void ACE_WindowManager::SetWindowSize(int width, int height)
{
    SDL_SetWindowSize(gameWindow, width, height);
}

void ACE_WindowManager::SetWindowPosition(int x, int y)
{
    SDL_SetWindowPosition(gameWindow, x, y);
    
}

/**
 * @deprecated replaced with SDL_CreateWindowAndRenderer
 */
bool ACE_WindowManager::CreateRenderer()
{
    if (gameWindow == nullptr) {return false;}
    gameRenderer = SDL_CreateRenderer(gameWindow, nullptr);
    return gameRenderer != nullptr;
}
