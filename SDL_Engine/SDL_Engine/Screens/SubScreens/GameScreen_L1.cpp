#include "GameScreen_L1.h"
#include "components/ACE_Texture2D.h"
#include "Managers/ACE_AudioManager.h"
#include "Managers/ACE_CollisionManager.h"
#include "Objects/Coin.h"
#include "Objects/POW_Block.h"
#include "components/ACE_TextRenderer.h""
GameScreen_L1::GameScreen_L1(SDL_Renderer* renderer) : GameScreen(renderer)
{
    SetUpLevel();
    textRenderer = new ACE_TextRenderer(renderer);
    textRenderer->LoadFontToText("Fonts/JetBrainsMono.ttf", 16);
    textRenderer->SetText("Hello World");
    textRenderer->SetTextColor(ACE_Color::Red());
    textRenderer->SetTextWrapping(0);
    textRenderer->SetTextOffset(25,50);
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
    delete newCoin;
    newCoin = nullptr;
    for (auto enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
    
}

void GameScreen_L1::Render()
{
    GameScreen::Render();
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->Render();
    }
    background_texture->Render(ACE_Vector2D(0, backgroundYPos), SDL_FLIP_NONE);
    player->Render();
    player2->Render();
    powBlock->Render();
    newCoin->Render();
    textRenderer->RenderText(100, 100);
    //RenderCollisionMap(renderer);
    ACE_Circle2D circle = ACE_Circle2D(50, ACE_Vector2D(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
    circle.DrawDebugCircle(renderer, ACE_Color::Red(), 1.0f);
}

void GameScreen_L1::Update(float deltaTime, SDL_Event* event)
{
    levelTime += deltaTime;
    GameScreen::Update(deltaTime, event);
    player->Update(deltaTime, event);
    player2->Update(deltaTime, event);
    newCoin->Update(deltaTime);
    UpdatePOWBlocks();
    UpdateEnemies(deltaTime, event);
    TimeSinceLastSpawn -= deltaTime;
    if (TimeSinceLastSpawn <= 0)
    {
        SpawnEnemy(ACE_Vector2D(150,32), FACING_RIGHT, 96.0f);
        SpawnEnemy(ACE_Vector2D(325,32), FACING_LEFT, 96.0f);
        TimeSinceLastSpawn = 5.0f;
    }
}

void GameScreen_L1::UpdatePOWBlocks()
{
    if (ACE_CollisionManager::Instance()->CheckCollision(powBlock->GetCollisionBox(), player->GetBoundingBox()))
    {
        if (player->IsJumping() && powBlock->isAvailable() )
        {
            DoScreenShake();
            powBlock->TakeHit();
            player->CancelJump();
        }
    }
}

void GameScreen_L1::UpdateEnemies(float deltaTime, SDL_Event* event)
{
    if (!enemies.empty())
    {
        int enemyIndexToDelete = -1;
        for (unsigned int i = 0; i < enemies.size(); i++)
        {
            if (enemies[i]->GetPosition().y > 300.0f)
            {
                if (enemies[i]->GetPosition().x < -(enemies[i]->GetWidth() / 2) || 
                    enemies[i]->GetPosition().x > SCREEN_WIDTH + (enemies[i]->GetWidth() / 2))
                {
                    enemies[i]->SetAlive(false); // if they're off the screen, kill em
                }
            }
            enemies[i]->Update(deltaTime, event);

            if (enemies[i]->GetPosition().y > 300.0f || enemies[i]->GetPosition().y <= 64.0f
                && enemies[i]->GetPosition().x < 64.0f || enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f) {}
            else if (ACE_CollisionManager::Instance()->CheckCollision(enemies[i]->GetBoundingBox(), player->GetBoundingBox()))
            {
                if (enemies[i]->IsInjured())
                {
                    enemies[i]->SetAlive(false);
                }
                else
                {
                    //kill mario
                }
            }
            if (enemies[i]->GetPosition().y > 300.0f && (enemies[i]->GetPosition().x < 64.0f || enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
            {
                enemyIndexToDelete = i;
            }
            else if (!enemies[i]->IsAlive())
            {
                enemyIndexToDelete = i;
            }
        }
        if (enemyIndexToDelete != -1)
        {
            delete enemies[enemyIndexToDelete];
            enemies.erase(enemies.begin() + enemyIndexToDelete);
            enemies.shrink_to_fit();
        }
    }
}

void GameScreen_L1::SpawnEnemy(ACE_Vector2D position, FACING_DIRECTION direction, float MoveSpeed)
{
    Character_Koopa* newKoopa = new Character_Koopa(renderer, SpriteData("images/Koopa.png", 1, 2), position, levelMap, direction, MoveSpeed);
    enemies.push_back(newKoopa);
}

void GameScreen_L1::DoScreenShake()
{
    GameScreen::DoScreenShake();
    for (int i = 0; i < enemies.size() ; i++)
    {
        enemies[i]->TakeDamage();
    }
}

void GameScreen_L1::RenderCollisionMap(SDL_Renderer* renderer)
{
    if (levelMap)
    {
        for (int i = 0; i < levelMap->GetMapHeight(); i++)
        {
            for (int j = 0; j < levelMap->GetMapWidth(); j++)
            {
                ACE_Color col = levelMap->GetTile(j,i) ? ACE_Color::Green() : ACE_Color::Red();
                ACE_Box2D currentTile = ACE_Box2D{float(j * TILE_WIDTH), float(i*TILE_HEIGHT), float(TILE_WIDTH), float(TILE_HEIGHT)};
                currentTile.DrawDebugRect(renderer, ACE_Color::Magenta(), false, 1.0f);
                currentTile.DrawDebugRect(renderer, col, true, 0.5f);
                
            }
        }
    }
}

bool GameScreen_L1::SetUpLevel()
{
    background_texture = new ACE_Texture2D(renderer);
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
    
    player = new Character_Mario(renderer, SpriteData("images/Mario.png"), ACE_Vector2D(64, 280), levelMap);
    if (player == nullptr)
    {
        std::cout << "Unable to load player" << std::endl;
        return false;       
    }

    player2 = new Character_Luigi(renderer, SpriteData("images/Luigi.png"), ACE_Vector2D(128, 290), levelMap);
    if (player2 == nullptr)
    {
        std::cout << "Unable to load player2" << std::endl;
        return false;       
    }
    
    newCoin = new Coin(renderer, ACE_Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    return true;
}

void GameScreen_L1::SetLevelMap()
{
    int map[MAP_HEIGHT][MAP_WIDTH] =
        {//   1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 1
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 2
            { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 }, // 3
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 4
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 5
            { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 }, // 6
            { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 }, // 7
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 8
            { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 }, // 9
            { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 }, // 10
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 11
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 12
            { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }  // 13
        };
    delete levelMap;
    levelMap = new ACE_LevelMap(map);
}
