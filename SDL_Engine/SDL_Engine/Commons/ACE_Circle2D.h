#pragma once
#include "ACE_Box2D.h"
#include "ACE_Vector2D.h"

struct ACE_Circle2D
{
	float radius;
	ACE_Vector2D position;

	ACE_Circle2D(float radius = 0.0f, ACE_Vector2D position = {0.0f,0.0f})
	{
		this->radius = radius;
		this->position = position;
	}

	bool Overlaps(ACE_Circle2D other)
	{
		return this->position.Distance(other.position) < this->radius + other.radius;
	}

	bool Contains(ACE_Circle2D other)
	{
		return this->position.Distance(other.position) < this->radius;
	}

	float signedDistance(ACE_Vector2D other)
	{
		return this->position.Distance(other) - radius;
	}

	void DrawDebugCircle(SDL_Renderer * renderer, ACE_Color color, float alpha = 0.75f)
	{
		/*
		 * https://stackoverflow.com/questions/38334081/how-to-draw-circles-arcs-and-vector-graphics-in-sdl
		 */
		const int32_t diameter = (radius * 2);

		int32_t x = (radius - 1);
		int32_t y = 0;
		int32_t tx = 1;
		int32_t ty = 1;
		int32_t error = (tx - diameter);

		SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, alpha * 255);
		
		while (x >= y)
		{
			
			//  Each of the following renders an octant of the circle
			SDL_RenderPoint(renderer, position.x + x, position.y - y);
			SDL_RenderPoint(renderer, position.x + x, position.y + y);
			SDL_RenderPoint(renderer, position.x - x, position.y - y);
			SDL_RenderPoint(renderer, position.x - x, position.y + y);
			SDL_RenderPoint(renderer, position.x + y, position.y - x);
			SDL_RenderPoint(renderer, position.x + y, position.y + x);
			SDL_RenderPoint(renderer, position.x - y, position.y - x);
			SDL_RenderPoint(renderer, position.x - y, position.y + x);

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

};
