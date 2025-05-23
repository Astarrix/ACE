#include "ACE_Texture2D.h"

#include "Commons/ACE_Box2D.h"


ACE_Texture2D::ACE_Texture2D(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

ACE_Texture2D::~ACE_Texture2D()
{
    Free();
    renderer = nullptr;
}

void ACE_Texture2D::Free()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        texture_width = 0;
        texture_height = 0;
    }   
}

bool ACE_Texture2D::LoadFromFile(std::string path)
{
    Free();
    SDL_Surface* p_surface = IMG_Load(path.c_str());
    if (p_surface == nullptr)
    {
        std::cout << "Unable to load surface " << path << " : " << SDL_GetError() << std::endl;
        return false;
    }
    //SDL_SetSurfaceColorKey(p_surface, true, SDL_MapRGB(SDL_GetPixelFormatDetails(p_surface->format),0, 0xFF, 0xFF, 0xFF));
    SDL_SetSurfaceBlendMode(p_surface, SDL_BLENDMODE_BLEND);
    texture = SDL_CreateTextureFromSurface(renderer, p_surface);

    if (texture == nullptr)
    {
        std::cout << "Unable to load image " << path << " : " << SDL_GetError() << std::endl;
        return false;
    }

    texture_width = p_surface->w;
    texture_height = p_surface->h;
    
    SDL_DestroySurface(p_surface);
    p_surface = nullptr;
    return texture != nullptr;
}

void ACE_Texture2D::Render(ACE_Vector2D Position, SDL_FlipMode flip, double angle, bool isScreenMapped)
{
    Position = isScreenMapped ? Position.WindowToScreen(renderer) : Position;
    const SDL_FRect renderlocation = {float(Position.x), float(Position.y), float(texture_width), float(texture_height)};
    SDL_RenderTextureRotated(renderer, texture, nullptr, &renderlocation, angle, nullptr, flip);
}

void ACE_Texture2D::Render(ACE_Box2D source, ACE_Box2D target, SDL_FlipMode flip, double angle, bool isScreenMapped)
{
    ACE_Vector2D screenMappedLoc = isScreenMapped ? ACE_Vector2D(target.x, target.y).WindowToScreen(renderer) : ACE_Vector2D(target.x, target.y);
    SDL_FRect src = {float(source.x), float(source.y), float(source.width), float(source.height)};
    SDL_FRect dst = {float(screenMappedLoc.x), float(screenMappedLoc.y), float(target.width), float(target.height)};
    SDL_RenderTextureRotated(renderer, texture, &src, &dst, angle, nullptr, flip);
}

