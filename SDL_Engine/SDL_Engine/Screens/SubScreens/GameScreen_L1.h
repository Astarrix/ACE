#pragma once
#include "Characters/SubCharacters/Character_Luigi.h"
#include "Screens/GameScreen.h"
#include "Characters/SubCharacters/Character_Mario.h"
#include "Managers/LevelMap.h"
class Texture2D;
class Character;
class POW_Block;

class GameScreen_L1 : GameScreen
{
public:
    GameScreen_L1(SDL_Renderer* renderer);
    ~GameScreen_L1();

    void Render() override;
    void Update(float deltaTime, SDL_Event* event) override;
    void UpdatePOWBlocks();
private:
    Texture2D* background_texture;
    bool SetUpLevel();
    void SetLevelMap();
    LevelMap* levelMap;
    Character_Mario* player;
    Character_Luigi* player2;
    POW_Block* powBlock;
};
