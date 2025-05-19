#pragma once
#include <vector>

#include "Characters/SubCharacters/Character_Koopa.h"
#include "Characters/SubCharacters/Character_Luigi.h"
#include "Screens/GameScreen.h"
#include "Characters/SubCharacters/Character_Mario.h"
#include "Managers/ACE_LevelMap.h"

class Coin;
class ACE_Texture2D;
class Character;
class POW_Block;
class ACE_TextRenderer;

class GameScreen_L1 : GameScreen
{
public:
    GameScreen_L1(SDL_Renderer* renderer);
    ~GameScreen_L1();

    void Render() override;
    void Update(float deltaTime, SDL_Event* event) override;
    void UpdatePOWBlocks();
    void UpdateEnemies(float deltaTime, SDL_Event* event);
    void SpawnEnemy(ACE_Vector2D position, FACING_DIRECTION direction, float MoveSpeed);
    void DoScreenShake() override;

    void RenderCollisionMap(SDL_Renderer* renderer);
    
private:
    ACE_Texture2D* background_texture;
    bool SetUpLevel();
    void SetLevelMap();
    ACE_LevelMap* levelMap;
    Character_Mario* player;
    Character_Luigi* player2;
    Coin* newCoin;
    POW_Block* powBlock;
    ACE_TextRenderer* textRenderer;
    std::vector<Character_Koopa*> enemies;
    float levelTime = 0.0f;
    float TimeSinceLastSpawn = 1.0f;
};
