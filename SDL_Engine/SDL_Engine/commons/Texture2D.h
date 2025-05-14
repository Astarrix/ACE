#pragma once
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "commons/Vector2D.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

#include "Box2D.h"

class Texture2D
{
public:
    Texture2D(SDL_Renderer* renderer);
    ~Texture2D();

    void Free();
    bool LoadFromFile(std::string path);
    void Render(Vector2D Position, SDL_FlipMode flip, double angle = 0.0f, bool isScreenMapped = false);
    void Render(Box2D source, Box2D target, SDL_FlipMode flip, double angle, bool isScreenMapped = false);

    float GetWidth() const { return texture_width; }
    float GetHeight() const { return texture_height; }

    SDL_Texture* GetTexture() const { return texture; }
protected:
    SDL_Texture* texture;
    
private:
    SDL_Renderer* renderer;

    int texture_width;
    int texture_height;
    
};

#endif