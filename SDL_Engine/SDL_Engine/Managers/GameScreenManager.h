#pragma once
#include "SDL3/SDL.h"

enum SCREENS
{
    SCREEN_INTRO,
    SCREEN_MENU,
    SCREEN_LEVEL1,
    SCREEN_LEVEL2,
    SCREEN_GAMEOVER,
    SCREEN_HIGHSCORE
};
class GameScreen;

class GameScreenManager
{
public:
    GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
    ~GameScreenManager();

    void Render();
    void Update(float deltaTime, SDL_Event* event);
    void ChangeScreen(SCREENS screen);
    

private:
    SDL_Renderer* renderer;
    GameScreen* currentScreen;
};
