#pragma once
#include <SDL3/SDL.h>

#include "Color.h"

struct Vector2D
{
    float x = 0.0f;
    float y = 0.0f;
    
    Vector2D(float inX = 0.0f, float inY = 0.0f)
    {
        x = inX;
        y = inY;
    }
    
    Vector2D WindowToScreen(SDL_Renderer* renderer)
    {
        int x, y;
        SDL_GetWindowPosition(SDL_GetRenderWindow(renderer), &x, &y);
        return {this->x - x, this->y - y};
    }
    Vector2D ScreenToWindow(SDL_Renderer* renderer)
    {
        int x, y;
        SDL_GetWindowPosition(SDL_GetRenderWindow(renderer), &x, &y);
        return {this->x + x, this->y + y};       
    }

    float Distance(Vector2D other)
    {
        return sqrtf(powf(other.x - x, 2) + powf(other.y - y, 2)); //sqrt(x2-x1)^2 + (y2-y1)^2
    }

    Vector2D Normalize()
    {
        float length = sqrtf(powf(x, 2) + powf(y, 2));
        return {x / length, y / length};
    }

    Vector2D operator+(Vector2D other)
    {
        return {x + other.x, y + other.y};
    }
    Vector2D operator+(int other)
    {
        return {x + other, y + other};
    }
    Vector2D operator+(float other)
    {
        return {x + other, y + other};
    }

    Vector2D operator-(Vector2D other)
    {
        return {x - other.x, y - other.y};
    }
    Vector2D operator-(int other)
    {
        return {x - other, y - other};
    }
    Vector2D operator-(float other)
    {
        return {x - other, y - other};
    }

    Vector2D operator*(Vector2D other)
    {
        return {x * other.x, y * other.y};
    }
    Vector2D operator*(int scalar)
    {
        return {x * scalar, y * scalar};
    }
    Vector2D operator*(float scalar)
    {
        return {x * scalar, y * scalar};
    }

    Vector2D operator/(Vector2D other)
    {
        return {x / other.x, y / other.y};
    }
    Vector2D operator/(int scalar)
    {
        return {x / scalar, y / scalar};
    }
    Vector2D operator/(float scalar)
    {
        return {x / scalar, y / scalar};
    }

    void DrawDebugPoint(SDL_Renderer* renderer, Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
        SDL_RenderPoint(renderer, x, y);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }


};
