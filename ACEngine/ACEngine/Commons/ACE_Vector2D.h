#pragma once
#include <iosfwd>
#include <iostream>
#include <SDL3/SDL.h>
#include "ACE_Color.h"

struct ACE_Vector2D
{
	float x = 0.0f;
	float y = 0.0f;

	ACE_Vector2D(float inX = 0.0f, float inY = 0.0f)
	{
		x = inX;
		y = inY;
	}

	ACE_Vector2D WindowToScreen(SDL_Renderer* renderer)
	{
		int x, y;
		SDL_GetWindowPosition(SDL_GetRenderWindow(renderer), &x, &y);
		return {this->x - x, this->y - y};
	}

	ACE_Vector2D ScreenToWindow(SDL_Renderer* renderer)
	{
		int x, y;
		SDL_GetWindowPosition(SDL_GetRenderWindow(renderer), &x, &y);
		return {this->x + x, this->y + y};
	}

	ACE_Vector2D Remap(ACE_Vector2D inMin = {0, 0}, ACE_Vector2D inMax = {1, 1}, ACE_Vector2D outMin = {0, 0},
	                   ACE_Vector2D outMax = {1, 1})
	{
		return {outMin + (*this - inMin) * (outMax - outMin) / (inMax - inMin)};
	}

	float Distance(ACE_Vector2D other)
	{
		return sqrtf(powf(other.x - x, 2) + powf(other.y - y, 2)); //sqrt(x2-x1)^2 + (y2-y1)^2
	}

	ACE_Vector2D Normalize()
	{
		float length = sqrtf(powf(x, 2) + powf(y, 2));
		return {x / length, y / length};
	}

	ACE_Vector2D operator+(ACE_Vector2D other)
	{
		return {x + other.x, y + other.y};
	}
	
	void operator+=(ACE_Vector2D other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(ACE_Vector2D other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(ACE_Vector2D other)
	{
		x *= other.x;
		y *= other.y;
	}

	void operator/=(ACE_Vector2D other)
	{
		x /= other.x;
		y /= other.y;
	}
	

	ACE_Vector2D operator+(int other)
	{
		return {x + other, y + other};
	}

	ACE_Vector2D operator+(float other)
	{
		return {x + other, y + other};
	}

	ACE_Vector2D operator-(ACE_Vector2D other)
	{
		return {x - other.x, y - other.y};
	}

	ACE_Vector2D operator-(int other)
	{
		return {x - other, y - other};
	}

	ACE_Vector2D operator-(float other)
	{
		return {x - other, y - other};
	}

	ACE_Vector2D operator*(ACE_Vector2D other)
	{
		return {x * other.x, y * other.y};
	}

	ACE_Vector2D operator*(int scalar)
	{
		return {x * scalar, y * scalar};
	}

	ACE_Vector2D operator*(float scalar)
	{
		return {x * scalar, y * scalar};
	}

	ACE_Vector2D operator/(ACE_Vector2D other)
	{
		return {x / other.x, y / other.y};
	}

	ACE_Vector2D operator/(int scalar)
	{
		return {x / scalar, y / scalar};
	}

	ACE_Vector2D operator/(float scalar)
	{
		return {x / scalar, y / scalar};
	}

	void DrawDebugPoint(SDL_Renderer* renderer, ACE_Color color)
	{
		SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
		SDL_RenderPoint(renderer, x, y);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
};
