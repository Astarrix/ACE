#pragma once
#include "Vector2D.h"

struct Line2D
{
	Vector2D start;
	Vector2D end;
	Line2D(Vector2D start = {0.0f, 0.0f}, Vector2D end = {0.0f, 0.0f})
	{
		this->start = start;
		this->end = end;
	}

	Line2D(Vector2D start, Vector2D direction, float length)
	{
		this->start = start;
		this->end = start + direction * length;
	}

	float Length()
	{
		return start.Distance(end);
	}

	Vector2D Direction()
	{
		return (end - start).Normalize();
	}

	Vector2D Center()
	{
		return (start + end) / 2.0f;
	}

	Vector2D Normal()
	{
		return Vector2D(-Direction().y, Direction().x);
	}

};
