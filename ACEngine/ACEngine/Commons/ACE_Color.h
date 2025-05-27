#pragma once
#include "SDL3/SDL.h"

struct ACE_Color
{
	Uint8 R;
	Uint8 G;
	Uint8 B;
	Uint8 A;

	constexpr ACE_Color(Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255, Uint8 alpha = 255)
		: R(red), G(green), B(blue), A(alpha) {}

	SDL_Color ToSDLColor() const { return {R, G, B, A}; }
	
	static constexpr ACE_Color Red() {return {255, 0, 0, 255};}
	static constexpr ACE_Color Green() { return {0, 255, 0, 255};}
	static constexpr ACE_Color Blue() { return {0, 0, 255, 255};}
	static constexpr ACE_Color White() { return {255, 255, 255, 255};}
	static constexpr ACE_Color Black() { return {0, 0, 0, 255};}
	static constexpr ACE_Color Transparent() { return {0, 0, 0, 0};}
	static constexpr ACE_Color Grey() { return {128, 128, 128, 255};}
	static constexpr ACE_Color Yellow() { return {255, 255, 0, 255};}
	static constexpr ACE_Color Orange() { return {255, 165, 0, 255};}
	static constexpr ACE_Color Pink() { return {255, 192, 203, 255};}
	static constexpr ACE_Color Purple() { return {128, 0, 128, 255};}
	static constexpr ACE_Color Brown() { return {165, 42, 42, 255};}
	static constexpr ACE_Color Cyan() { return {0, 255, 255, 255};}
	static constexpr ACE_Color Magenta() { return {255, 0, 255, 255};}
	static constexpr ACE_Color LightBlue() { return {173, 216, 230, 255};}
	static constexpr ACE_Color LightGreen() { return {144, 238, 144, 255};}
	static constexpr ACE_Color LightRed() { return {255, 140, 140, 255};}
	static constexpr ACE_Color LightYellow() { return {255, 255, 140, 255};}
	static constexpr ACE_Color LightPurple() { return {176, 196, 222, 255};}
	static constexpr ACE_Color LightBrown() { return {211, 176, 140, 255};}
	static constexpr ACE_Color LightCyan() { return {173, 255, 255, 255};}
	static constexpr ACE_Color LightMagenta() { return {255, 182, 193, 255};}
	static constexpr ACE_Color LightGrey() { return {200, 200, 200, 255};}
	
};
