#pragma once
#include "Objects/Components/ACE_Component.h"
#include <iostream>
#include "SDL3_image/SDL_image.h"

class ACE_Texture2D : public ACE_Component
{
public:
	ACE_Texture2D() = default;
	~ACE_Texture2D() override;

	bool LoadTextureFromFile(SDL_Renderer* inRenderer, const char* fileName);
	void Render(SDL_FlipMode flip = SDL_FLIP_NONE);
	void RenderPortion(SDL_FRect portion, SDL_FlipMode flip = SDL_FLIP_NONE);

	int GetTextureWidth() const {return texWidth;}
	int GetTextureHeight() const {return texHeight;}
private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	int texWidth = 0, texHeight = 0;
	void FreeTexture();
};
