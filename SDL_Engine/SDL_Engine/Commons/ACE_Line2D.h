#pragma once
#include "ACE_Vector2D.h"

struct ACE_Line2D
{
	ACE_Vector2D start;
	ACE_Vector2D end;
	ACE_Line2D(ACE_Vector2D start = {0.0f, 0.0f}, ACE_Vector2D end = {0.0f, 0.0f})
	{
		this->start = start;
		this->end = end;
	}

	ACE_Line2D(ACE_Vector2D start, ACE_Vector2D direction, float length)
	{
		this->start = start;
		this->end = start + direction * length;
	}

	float Length()
	{
		return start.Distance(end);
	}

	ACE_Vector2D Direction()
	{
		return (end - start).Normalize();
	}

	ACE_Vector2D Center()
	{
		return (start + end) / 2.0f;
	}

	ACE_Vector2D Normal()
	{
		return ACE_Vector2D(-Direction().y, Direction().x);
	}

	void DrawDebugLine(SDL_Renderer * renderer, ACE_Color color, float alpha = 0.75f)
	{
		SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, alpha * 255);
		SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
};
