#pragma once
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "commons/Vector2D.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

class Texture2D
{
public:
    Texture2D(SDL_Renderer* renderer);
    ~Texture2D();

    void Free();
    bool LoadFromFile(std::string path);
    void Render(Vector2D Position, SDL_FlipMode flip, double angle = 0.0f);

    float GetWidth() const { return m_width; }
    float GetHeight() const { return m_height; }
    
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    int m_width;
    int m_height;
    
};

#endif