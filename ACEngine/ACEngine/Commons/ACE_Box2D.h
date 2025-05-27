#pragma once

#include "ACE_Color.h"
#include "Commons/ACE_Vector2D.h"

struct ACE_Box2D
{
	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;

	ACE_Box2D(float inX = 0.0f, float inY = 0.0f, float inWidth = 2.5f, float inHeight = 2.5f)
	{
		x = inX;
		y = inY;
		width = inWidth;
		height = inHeight;
	}

	SDL_FRect ToSDLRect() const
	{
		return {x, y, width, height};
	}

	ACE_Box2D FromSDLRect(SDL_FRect rect)
	{
		return {rect.x, rect.y, rect.w, rect.h};
	}

	bool Overlaps(ACE_Box2D other)
	{
		return
			this->x < other.x + other.width &&
			this->x + this->width > other.x &&
			this->y < other.y + other.height &&
			this->y + this->height > other.y;
	}

	bool Contains(ACE_Box2D other)
	{
		return
			this->x < other.x &&
			this->y < other.y &&
			this->x + this->width > other.x + other.width &&
			this->y + this->height > other.y + other.height;
	}

	bool Contains(ACE_Vector2D other)
	{
		return
			this->x < other.x &&
			this->y < other.y &&
			this->x + this->width > other.x &&
			this->y + this->height > other.y;
	}

	ACE_Vector2D GetCenter()
	{
		return {x + width / 2, y + height / 2};
	}

	float DistanceToCenter(ACE_Vector2D other)
	{
		return other.Distance(GetCenter());
	}

	void Resize(ACE_Vector2D newSize)
	{
		this->width = newSize.x;
		this->height = newSize.y;
	}

	ACE_Box2D ScaleBox(ACE_Vector2D scale)
	{
		return {x, y, width * scale.x, height * scale.y};
	}


	void Move(ACE_Vector2D newPosition)
	{
		this->x = newPosition.x;
		this->y = newPosition.y;
	}

	float GetArea()
	{
		return width * height;
	}

	float GetPerimeter()
	{
		return 2 * (width + height);
	}

	float GetDiagonal()
	{
		return sqrtf(powf(width, 2) + powf(height, 2)); // sqrt(a^2 + b^2) = c
	}

	float GetLongestSide()
	{
		return (width > height) ? width : height;
	}

	float GetShortestSide()
	{
		return (width < height) ? width : height;
	}

	void Rotate90()
	{
		float temp = width;
		width = height;
		height = temp;
	}

	void DrawDebugRect(SDL_Renderer* renderer, ACE_Color color, bool isFilled = false, float alpha = 0.75f)
	{
		SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, alpha * 255);
		auto rect = new SDL_FRect{x, y, width, height};
		isFilled
			? SDL_RenderFillRect(renderer, rect)
			: SDL_RenderRect(renderer, rect);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		delete rect;
	}
};
