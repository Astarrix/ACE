#pragma once
#include "Components/ACE_Sprite2D.h"
#include "Components/ACE_Texture2D.h"
#include "Commons/ACE_Box2D.h"
#include "Commons/ACE_Circle2D.h"
#include "Commons/ACE_Vector2D.h"
#include "Managers/ACE_LevelMap.h"
#include "SDL3/SDL_render.h"

enum FACING_DIRECTION
{
    FACING_LEFT,
    FACING_RIGHT
};

class Character
{
#define INITIAL_JUMP_FORCE 700.0f
#define JUMP_FORCE_DECREMENT 600.0f
public:
    Character(SDL_Renderer* renderer, SpriteData spriteData, ACE_Vector2D initPosition = ACE_Vector2D(0.0,0.0), ACE_LevelMap* map = nullptr);
    virtual ~Character();
    virtual void Render();
    virtual void Update(float deltaTime, SDL_Event* event);
    
    void SetPosition(ACE_Vector2D newPosition);
    ACE_Vector2D GetPosition() const { return position; }
    ACE_Box2D GetBoundingBox() const;
    ACE_Circle2D GetBoundingCircle() const;
    
    virtual void Move(float deltaTime, ACE_Vector2D direction);
    virtual void Jump(float inJumpForce = INITIAL_JUMP_FORCE);
    virtual void AddGravity(float deltaTime);

    bool IsJumping() {return isJumping;}
    void CancelJump() {isJumping = false;}

    bool IsAlive() {return isAlive;}
    void SetAlive(bool alive) {isAlive = alive;}

    float GetWidth() const { return sprite->GetSpriteWidth(); }
    float GetHeight() const { return sprite->GetSpriteHeight(); }

    void PrintCharacterInfo();
protected:
    SDL_Renderer* renderer;
    ACE_Vector2D position;
    ACE_Sprite2D* sprite;
    FACING_DIRECTION facingDirection;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool isJumping = false;
    bool canJump = true;
    float jumpForce = 0;
    float MovementSpeed = 100.0f;
    float Mass = 30.0f;
    bool isAlive = true;
private:
    ACE_LevelMap* levelMap;
};
