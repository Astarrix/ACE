#include "ACE_WindowManager.h"

bool ACE_WindowManager::CreateWindow()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "SDL Test Window",                  // Window title
        INIT_SCREEN_WIDTH,                       // Width
        INIT_SCREEN_HEIGHT,                      // Height
        SDL_WINDOW_RESIZABLE                // Window flags
    );

    
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit(); //force exit the program
        return false;
    }
    gameWindow = window;
    CreateRenderer();
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

intBox2D ACE_WindowManager::GetWindowSize()
{
    intBox2D size;
    SDL_GetWindowSize(gameWindow, &size.width, &size.height);
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

bool ACE_WindowManager::CreateRenderer()
{
    if (gameWindow == nullptr) {return false;}
    gameRenderer = SDL_CreateRenderer(gameWindow, nullptr);
    return gameRenderer != nullptr;
}
