#pragma once
#include "SDL3/SDL.h"

struct Color
{
	Uint8 R;
	Uint8 G;
	Uint8 B;
	Uint8 A;
	Color(Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255, Uint8 alpha = 255)
	{
		this->R = red;
		this->G = green;
		this->B = blue;
		this->A = alpha;
	}
	static Color Red() {return Color(255, 0, 0, 255);}
	static Color Green() { return Color(0, 255, 0, 255);}
	static Color Blue() { return Color(0, 0, 255, 255);}
};
