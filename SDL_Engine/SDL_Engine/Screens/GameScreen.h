#pragma once
#include <SDL3/SDL.h>
class GameScreen
{
public:
    GameScreen(SDL_Renderer* renderer);
    ~GameScreen();

    virtual void Render() {};
    virtual void Update(float deltaTime, SDL_Event* event) {};
protected:
    SDL_Renderer* renderer;
private:
    
};
