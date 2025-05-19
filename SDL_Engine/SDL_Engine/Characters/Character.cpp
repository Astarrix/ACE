#include "Character.h"

#include "Commons/ACE_Constants.h"


Character::Character(SDL_Renderer* renderer, SpriteData spriteData, ACE_Vector2D initPosition, ACE_LevelMap* map)
{
    this->renderer = renderer;
    position = initPosition;
    sprite = new ACE_Sprite2D(renderer);
    sprite->LoadSpriteSheetFromFile(spriteData);
    levelMap = map;
}

Character::~Character()
{
    delete sprite;
    sprite = nullptr;
    this->renderer = nullptr;
    levelMap = nullptr;
}

void Character::Render()
{
    SDL_FlipMode flip = facingDirection == FACING_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    sprite->RenderSprite(position, flip);
    
    int centralXPosition = int(position.x + (sprite->GetSpriteWidth() / 2)) / TILE_WIDTH;
    int footPosition = int(position.y + sprite->GetSpriteHeight()) / TILE_HEIGHT;

    if (bool DrawFootPos = false)
    {
        ACE_Box2D box = ACE_Box2D(centralXPosition * TILE_WIDTH, footPosition * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
        box.DrawDebugRect(renderer, ACE_Color::Green(), true);
        GetBoundingBox().DrawDebugRect(renderer, ACE_Color::Red());
    }
}

void Character::Update(float deltaTime, SDL_Event* event)
{
    ACE_Vector2D direction;
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
    int CentralXPosition = int(position.x + sprite->GetSpriteWidth() / 2) / TILE_WIDTH;
    int footPosition = int(position.y + sprite->GetSpriteHeight()) / TILE_HEIGHT;
    if (levelMap && levelMap->GetTile(CentralXPosition, footPosition) == 1)
    {
        canJump = true;
    }
    else
    {
        AddGravity(deltaTime);
    }

}

void Character::SetPosition(ACE_Vector2D newPosition)
{
    position = newPosition;
}

ACE_Box2D Character::GetBoundingBox() const
{
    ACE_Box2D box;
    box.x = position.x;
    box.y = position.y;
    box.width = sprite->GetSpriteWidth();
    box.height = sprite->GetSpriteHeight();
    return box;
}

ACE_Circle2D Character::GetBoundingCircle() const
{
    ACE_Circle2D circle;
    circle.radius = sprite->GetSpriteWidth() / 2;
    circle.position = position;
    return circle;
}

void Character::Move(float deltaTime, ACE_Vector2D direction)
{
    facingDirection = direction.x > 0 ? FACING_RIGHT : FACING_LEFT;
    position.x += direction.Normalize().x * MovementSpeed * deltaTime;
}

void Character::Jump(float inJumpForce)
{
    jumpForce = inJumpForce;
    isJumping = true;
    canJump = false;
}


void Character::AddGravity(float deltaTime)
{
    int centralXPosition = int(position.x + sprite->GetSpriteWidth() / 2) / TILE_WIDTH;
    int footPosition = int(position.y + sprite->GetSpriteHeight()) / TILE_HEIGHT;
    
    if (!levelMap->GetTile(centralXPosition, footPosition))
    {
        position.y += GRAVITY * Mass * deltaTime;
    }
    else
    {
        // Snap to tile top
        position.y = (footPosition * TILE_HEIGHT) - sprite->GetSpriteHeight();
    }
}

void Character::PrintCharacterInfo()
{
    std::cout << "Character Position: " << position.x << ", " << position.y << std::endl;
    std::cout << "Character Sprite Width: " << sprite->GetSpriteWidth() << std::endl;
    std::cout << "Character Sprite Height: " << sprite->GetSpriteHeight() << std::endl;
}

