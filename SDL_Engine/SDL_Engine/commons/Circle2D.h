#pragma once
#include "Box2D.h"
#include "Vector2D.h"

struct Circle2D
{
	float radius;
	Vector2D position;

	Circle2D(float radius = 0.0f, Vector2D position = {0.0f,0.0f})
	{
		this->radius = radius;
		this->position = position;
	}

	bool Overlaps(Circle2D other)
	{
		return this->position.Distance(other.position) < this->radius + other.radius;
	}

	bool Contains(Circle2D other)
	{
		return this->position.Distance(other.position) < this->radius;
	}

	float signedDistance(Vector2D other)
	{
		return this->position.Distance(other) - radius;
	}
	
};
