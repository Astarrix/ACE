#include "GameScreen_L1.h"
#include "commons/Texture2D.h"
#include "Managers/CollisionManager.h"
#include "Objects/POW_Block.h"
GameScreen_L1::GameScreen_L1(SDL_Renderer* renderer) : GameScreen(renderer)
{
    SetUpLevel();
}

GameScreen_L1::~GameScreen_L1()
{
    delete background_texture;
    background_texture = nullptr;
    delete player;
    delete player2;
    delete powBlock;
    player = nullptr;
    player2 = nullptr;
    powBlock = nullptr;
}

void GameScreen_L1::Render()
{
    GameScreen::Render();
    background_texture->Render(Vector2D(0, backgroundYPos), SDL_FLIP_NONE);
    player->Render();
    player2->Render();
    powBlock->Render();
}

void GameScreen_L1::Update(float deltaTime, SDL_Event* event)
{
    GameScreen::Update(deltaTime, event);
    player->Update(deltaTime, event);
    player2->Update(deltaTime, event);
    UpdatePOWBlocks();
    
    if (CollisionManager::Instance()->CheckCollision(player, player2))
    {
        player->Jump();       
    }
}

void GameScreen_L1::UpdatePOWBlocks()
{
    if (CollisionManager::Instance()->CheckCollision(powBlock->GetCollisionBox(), player->GetBoundingBox()))
    {
        if (player->IsJumping())
        {
            DoScreenShake();
            powBlock->TakeHit();
            player->CancelJump();
        }
    }
}

bool GameScreen_L1::SetUpLevel()
{
    background_texture = new Texture2D(renderer);
    if (!background_texture->LoadFromFile("images/BackgroundMB.png"))
    {
        std::cout << "Unable to load background texture" << std::endl;
        return false;       
    }
    SetLevelMap();
    powBlock = new POW_Block(renderer, levelMap);
    if (powBlock == nullptr)
    {
        std::cout << "Unable to load powBlock" << std::endl;
        return false;      
    }
    player = new Character_Mario(renderer, "images/Mario.png", Vector2D(64, 330), levelMap);
    if (player == nullptr)
    {
        std::cout << "Unable to load player" << std::endl;
        return false;       
    }
    player2 = new Character_Luigi(renderer, "images/Luigi.png", Vector2D(64, 330), levelMap);
    if (player2 == nullptr)
    {
        std::cout << "Unable to load player2" << std::endl;
        return false;       
    }
    return true;
}

void GameScreen_L1::SetLevelMap()
{
    int map[MAP_HEIGHT][MAP_WIDTH] =
        {
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
            { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
            { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
            { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
            { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
            { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
            { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
        };
    delete levelMap;
    levelMap = new LevelMap(map);
}
