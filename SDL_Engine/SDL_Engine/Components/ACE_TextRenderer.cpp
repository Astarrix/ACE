#include "ACE_TextRenderer.h"

ACE_TextRenderer::ACE_TextRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

ACE_TextRenderer::~ACE_TextRenderer()
{
	TTF_CloseFont(font);
	renderer = nullptr;
	textEngine = nullptr;
	textObject = nullptr;
	font = nullptr;
}

bool ACE_TextRenderer::LoadFontToText(std::string fontPath, int fontSize)
{
	if (renderer == nullptr)
	{
		std::cout << "Renderer is null" << std::endl;
		return false;
	}
	textEngine = TTF_CreateRendererTextEngine(renderer);
	if (textEngine == nullptr)
	{
		std::cout << "Unable to create text engine" << SDL_GetError() << std::endl;
		return false;
	}
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (font == nullptr)
	{
		std::cout << "Unable to load font" << SDL_GetError() << std::endl;
		return false;
	}
	textObject = TTF_CreateText(textEngine, font, nullptr, 0);
	if (textObject == nullptr)
	{
		std::cout << "Unable to create text object" << SDL_GetError() << std::endl;
		return false;
	}
	if (!TTF_SetTextEngine(textObject, textEngine))
	{
		std::cout << "Unable to set text engine" << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool ACE_TextRenderer::SetText(std::string text)
{
	if (textObject == nullptr)
	{
		std::cout << "Text object is null" << std::endl;
		return false;
	}
	if (!TTF_SetTextString(textObject, text.c_str(), text.length()))
	{
		std::cout << "Unable to set text" << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool ACE_TextRenderer::SetTextColor(ACE_Color color)
{
	if (textObject == nullptr)
	{
		std::cout << "Text object is null" << std::endl;
		return false;
	}
	if (!TTF_SetTextColor(textObject, color.R, color.G, color.B, color.A))
	{
		std::cout << "Unable to set text color" << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool ACE_TextRenderer::SetTextOffset(int x, int y)
{
	if (textObject == nullptr)
	{
		std::cout << "Text object is null" << std::endl;
		return false;
	}
	if (!TTF_SetTextPosition(textObject, x, y))
	{
		std::cout << "Unable to set text position" << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool ACE_TextRenderer::ChangeTextFont(std::string fontPath, int fontSize)
{
	if (textObject == nullptr)
	{
		std::cout << "Text object is null" << std::endl;
		return false;
	}
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (font == nullptr)
	{
		std::cout << "Unable to load font" << SDL_GetError() << std::endl;
		return false;
	}
	if (!TTF_SetTextFont(textObject, font))
	{
		std::cout << "Unable to set text font" << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool ACE_TextRenderer::SetTextStyle(TTF_FontStyleFlags style)
{
	if (textObject == nullptr)
	{
		std::cout << "Text object is null" << std::endl;
		return false;
	}
	TTF_SetFontStyle(font, style);
	return true;
}

bool ACE_TextRenderer::SetTextWrapping(int width)
{
	if (textObject == nullptr)
	{
		std::cout << "Text object is null" << std::endl;
		return false;
	}
	if (!TTF_SetTextWrapWidth(textObject, width))
	{
		std::cout << "Unable to set text wrapping width. " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}


void ACE_TextRenderer::RenderText(int x, int y)
{
	if (textObject == nullptr)
	{
		std::cout << "Text object is null" << std::endl;
		return;
	}
	TTF_DrawRendererText(textObject, x, y);
}
