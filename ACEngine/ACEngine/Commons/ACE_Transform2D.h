#pragma once
#include "ACE_Vector2D.h"

struct ACE_Transform2D
{
	ACE_Vector2D position;
	ACE_Vector2D scale;
	float angle;
	ACE_Transform2D(int xPos = 0, int yPos = 0, int xScale = 1.0f, int yScale = 1.0f, float angle = 0 )
	{
		position = ACE_Vector2D(xPos, yPos);
		scale = ACE_Vector2D(xScale, yScale);
		this->angle = angle;
	}
};
