#include "Character.h"

#include "commons/constants.h"


Character::Character(SDL_Renderer* renderer, std::string imgPath, Vector2D initPosition, LevelMap* map)
{
    this->renderer = renderer;
    position = initPosition;
    texture = new Texture2D(renderer);
    texture->LoadFromFile(imgPath);
    levelMap = map;
}

Character::~Character()
{
    this->renderer = nullptr;
}

void Character::Render()
{
    SDL_FlipMode flip = facingDirection == FACING_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    texture->Render(position, flip);
}

void Character::Update(float deltaTime, SDL_Event* event)
{
    Vector2D direction;
    direction.x = isMovingRight ? 1.0f : isMovingLeft ? -1.0f : 0.0f;
    if (direction.x > 0 || direction.x < 0) { Move(deltaTime, direction);}
    if (isJumping)
    {
        position.y -= jumpForce * deltaTime;
        jumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
        if (jumpForce <= 0)
        {
            isJumping = false;
        }
    }
    int CentralXPosition = int(position.x + texture->GetWidth() / 2) / TILE_WIDTH;
    int footPosition = int(position.y + texture->GetHeight()) / TILE_HEIGHT;
    if (levelMap && levelMap->GetTile(CentralXPosition, footPosition) == 1)
    {
        canJump = true;
    }
    else
    {
        AddGravity(deltaTime);
    }

}

void Character::SetPosition(Vector2D newPosition)
{
    position = newPosition;
}

Box2D Character::GetBoundingBox() const
{
    Box2D box;
    box.x = position.x;
    box.y = position.y;
    box.width = texture->GetWidth();
    box.height = texture->GetHeight();
    return box;
}

Circle2D Character::GetBoundingCircle() const
{
    Circle2D circle;
    circle.radius = texture->GetWidth() / 2;
    circle.position = position;
    return circle;
}

void Character::Move(float deltaTime, Vector2D direction)
{
    facingDirection = direction.x > 0 ? FACING_RIGHT : FACING_LEFT;
    position.x += direction.Normalize().x * MovementSpeed * deltaTime;
}

void Character::Jump()
{
    jumpForce = INITIAL_JUMP_FORCE;
    isJumping = true;
    canJump = false;
}


void Character::AddGravity(float deltaTime)
{
    int x,y,w,h;
    SDL_GetWindowPosition(SDL_GetRenderWindow(renderer), &x, &y);
    SDL_GetWindowSize(SDL_GetRenderWindow(renderer), &w, &h);
    
    if (position.y < h - texture->GetHeight()) // if above the screen
    {
        position.y += GRAVITY * Mass * deltaTime;
    } else if (position.y > h - texture->GetHeight()) // if set below the screen
    {
        position.y = h - texture->GetHeight();
    }
    else
    {
        canJump = true;
    }
}

