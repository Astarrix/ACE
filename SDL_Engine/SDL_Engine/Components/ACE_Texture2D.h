#pragma once
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Commons/ACE_Vector2D.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

#include "Commons/ACE_Box2D.h"

class ACE_Texture2D
{
public:
    ACE_Texture2D(SDL_Renderer* renderer);
    ~ACE_Texture2D();

    void Free();
    bool LoadFromFile(std::string path);
    void Render(ACE_Vector2D Position, SDL_FlipMode flip, double angle = 0.0f, bool isScreenMapped = false);
    void Render(ACE_Box2D source, ACE_Box2D target, SDL_FlipMode flip, double angle, bool isScreenMapped = false);

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