#pragma once
#include "commons/Texture2D.h"
#include "commons/Box2D.h"
#include "commons/Circle2D.h"
#include "commons/Vector2D.h"
#include "Managers/LevelMap.h"
#include "SDL3/SDL_render.h"

enum FACING_DIRECTION
{
    FACING_LEFT,
    FACING_RIGHT
};

class Character
{
public:
    Character(SDL_Renderer* renderer, std::string imgPath, Vector2D initPosition = Vector2D(0.0,0.0), LevelMap* map = nullptr);
    ~Character();
    virtual void Render();
    virtual void Update(float deltaTime, SDL_Event* event);
    
    void SetPosition(Vector2D newPosition);
    Vector2D GetPosition() const { return position; }
    Box2D GetBoundingBox() const;
    Circle2D GetBoundingCircle() const;
    
    virtual void Move(float deltaTime, Vector2D direction);
    virtual void Jump();
    virtual void AddGravity(float deltaTime);

    bool IsJumping() {return isJumping;}
    void CancelJump() {isJumping = false;}
protected:
    SDL_Renderer* renderer;
    Vector2D position;
    Texture2D* texture;
    FACING_DIRECTION facingDirection;
    bool isMovingRight;
    bool isMovingLeft;
    bool isJumping;
    bool canJump;
    float jumpForce;
    float MovementSpeed = 100.0f;
    float Mass = 20.0f;
private:
    LevelMap* levelMap;
};
