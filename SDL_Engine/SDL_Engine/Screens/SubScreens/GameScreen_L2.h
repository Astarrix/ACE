#pragma once

#include "Screens/GameScreen.h"
class ACE_Texture2D;


class GameScreen_L2 : GameScreen
{
public:
    GameScreen_L2(SDL_Renderer* renderer);
    ~GameScreen_L2();

    void Render() override;
    void Update(float deltaTime, SDL_Event* event) override;
private:
    ACE_Texture2D* background_texture;
    bool SetUpLevel();
};
