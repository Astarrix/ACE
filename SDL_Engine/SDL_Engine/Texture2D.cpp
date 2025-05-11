#include "Texture2D.h"


Texture2D::Texture2D(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

Texture2D::~Texture2D()
{
    Free();
    renderer = nullptr;
}

void Texture2D::Free()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        m_width = 0;
        m_height = 0;
    }   
}

bool Texture2D::LoadFromFile(std::string path)
{
    Free();
    SDL_Surface* p_surface = IMG_Load(path.c_str());
    if (p_surface == nullptr)
    {
        std::cout << "Unable to load surface " << path << " : " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetSurfaceColorKey(p_surface, true, SDL_MapRGB(SDL_GetPixelFormatDetails(p_surface->format),0, 0xFF, 0xFF, 0xFF));
    texture = SDL_CreateTextureFromSurface(renderer, p_surface);

    if (texture == nullptr)
    {
        std::cout << "Unable to load image " << path << " : " << SDL_GetError() << std::endl;
        return false;
    }

    m_width = p_surface->w;
    m_height = p_surface->h;
    
    SDL_DestroySurface(p_surface);
    p_surface = nullptr;
    return texture != nullptr;
}

void Texture2D::Render(Vector2D Position, SDL_FlipMode flip, double angle)
{
    const SDL_FRect renderlocation = {float(Position.x), float(Position.y), float(m_width), float(m_height)};
    SDL_RenderTextureRotated(renderer, texture, nullptr, &renderlocation, angle, nullptr, flip);
}
