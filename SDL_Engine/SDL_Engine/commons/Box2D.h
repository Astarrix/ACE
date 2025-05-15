#pragma once

#include "Color.h"
#include "commons/Vector2D.h"

struct Box2D
{
	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;

	Box2D(float inX = 0.0f, float inY = 0.0f, float inWidth = 0.0f, float inHeight = 0.0f)
	{
		x = inX;
		y = inY;
		width = inWidth;
		height = inHeight;
	}

	bool Overlaps(Box2D other)
	{
		return
			this->x < other.x + other.width &&
			this->x + this->width > other.x &&
			this->y < other.y + other.height &&
			this->y + this->height > other.y;
	}

	bool Contains(Box2D other)
	{
		return
			this->x < other.x &&
			this->y < other.y &&
			this->x + this->width > other.x + other.width &&
			this->y + this->height > other.y + other.height;
	}

	Vector2D GetCenter()
	{
		return {x + width / 2, y + height / 2};
	}

	float DistanceToCenter(Vector2D other)
	{
		return other.Distance(GetCenter());
	}

	void Resize(Vector2D newSize)
	{
		this->width = newSize.x;
		this->height = newSize.y;
	}

	void Move(Vector2D newPosition)
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

	void DrawDebugRect(SDL_Renderer* renderer, Color color, bool isFilled = false)
	{
		SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
		isFilled
			? SDL_RenderFillRect(renderer, new SDL_FRect{x, y, width, height})
			: SDL_RenderRect(renderer, new SDL_FRect{x, y, width, height});
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

	Box2D ScaleBox(Vector2D scale)
	{
		return {x, y, width * scale.x, height * scale.y};
	}
};
