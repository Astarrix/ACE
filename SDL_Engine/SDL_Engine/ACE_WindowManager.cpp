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

void ACE_WindowManager::Render(SDL_Texture* gTexture, intBox2D imageProperties)
{
    const SDL_FRect renderlocation = {float(imageProperties.x), float(imageProperties.y), float(imageProperties.width), float(imageProperties.height)};
    
    SDL_SetRenderDrawColor(GetRenderer(), 0XFF, 0XFF, 0XFF, 0XFF);
    SDL_RenderClear(GetRenderer());
    SDL_RenderTextureRotated(GetRenderer(), gTexture, nullptr, &renderlocation, 0, nullptr, SDL_FLIP_NONE);
    SDL_RenderPresent(GetRenderer());
}

bool ACE_WindowManager::CreateRenderer()
{
    if (gameWindow == nullptr) {return false;}
    gameRenderer = SDL_CreateRenderer(gameWindow, nullptr);
    return gameRenderer != nullptr;
}

SDL_Texture* ACE_WindowManager::LoadTextureFromFile(std::string path)
{
    SDL_Surface* p_surface = IMG_Load(path.c_str());
    if (p_surface == nullptr)
    {
        std::cout << "Unable to load surface " << path << " : " << SDL_GetError() << std::endl;
        return nullptr;
    }
    
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(GetRenderer(), p_surface);
    if (p_texture == nullptr)
    {
        std::cout << "Unable to load image " << path << " : " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_DestroySurface(p_surface);
    return p_texture;
}

void ACE_WindowManager::FreeTexture(SDL_Texture*& gTexture)
{
    if (gTexture != nullptr)
    {
        SDL_DestroyTexture(gTexture);
        gTexture = nullptr;
    }   
}