#pragma once

#include "Screens/GameScreen.h"
class Texture2D;


class GameScreen_L2 : GameScreen
{
public:
    GameScreen_L2(SDL_Renderer* renderer);
    ~GameScreen_L2();

    void Render() override;
    void Update(float deltaTime, SDL_Event* event) override;
private:
    Texture2D* background_texture;
    bool SetUpLevel();
};
