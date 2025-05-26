#pragma once
#include <iostream>

#include "Commons/ACE_Box2D.h"
#include "Commons/ACE_Color.h"
#include "Objects/Components/ACE_Component.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"

class ACE_TextRenderer : public ACE_Component
{
public:
	ACE_TextRenderer(SDL_Renderer* renderer);
	~ACE_TextRenderer();
	
	bool LoadFontToText(std::string fontPath, int fontSize);
	bool SetText(std::string text);
	bool SetTextColor(ACE_Color color);
	void SetTextOffset(int x, int y) {this->xOffset = x; this->yOffset = y;};
	bool ChangeTextFont(std::string fontPath, int fontSize);
	bool SetTextStyle(TTF_FontStyleFlags style);
	bool SetTextWrapping(int width = 0);
	void RenderText(int x, int y);
	
	
private:
	int xOffset = 0, yOffset = 0;
	SDL_Renderer* renderer;
	TTF_Font* font;
	TTF_Text* textObject;
	TTF_TextEngine* textEngine;
};
