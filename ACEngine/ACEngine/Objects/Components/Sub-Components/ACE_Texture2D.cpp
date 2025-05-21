#include "ACE_Texture2D.h"
#include "Objects/Actors/ACE_Actor.h"

ACE_Texture2D::~ACE_Texture2D()
{
	FreeTexture();
	renderer = nullptr;
}

bool ACE_Texture2D::LoadTextureFromFile(SDL_Renderer* inRenderer, const char* fileName)
{
	if (inRenderer == nullptr)
	{
		std::cout << "Renderer is null" << std::endl;
		return false;
	}
	this->renderer = inRenderer;
	
	FreeTexture(); // so if this func is called again it's not going to leak memory.
	SDL_Surface* l_surface = IMG_Load(fileName);
	
	if (l_surface == nullptr)
	{
		std::cout << "Unable to load surface " << fileName << " : " << SDL_GetError() << std::endl;
		return false;
	}
	texture = SDL_CreateTextureFromSurface(this->renderer, l_surface);

	if (texture == nullptr)
	{
		std::cout << "Unable to load image " << fileName << " : " << SDL_GetError() << std::endl;
		return false;
	}
	
	texWidth = l_surface->w;
	texHeight = l_surface->h;
    
	SDL_DestroySurface(l_surface);
	l_surface = nullptr;
	return texture != nullptr;
}

void ACE_Texture2D::Render()
{
	const SDL_FRect l_renderLocation =
		{
		float(parent->GetTransform().position.x),
		float(parent->GetTransform().position.y),
		float(parent->GetTransform().scale.x * texWidth),
		float(parent->GetTransform().scale.y * texHeight)
		};
	SDL_RenderTextureRotated(renderer, texture, nullptr, &l_renderLocation, parent->GetTransform().angle, nullptr, SDL_FLIP_NONE);
}

void ACE_Texture2D::RenderPortion(SDL_FRect portion)
{
	const SDL_FRect l_renderLocation =
	{
		float(parent->GetTransform().position.x),
		float(parent->GetTransform().position.y),
		float(parent->GetTransform().scale.x * texWidth),
		float(parent->GetTransform().scale.y * texHeight)
	};
	SDL_RenderTextureRotated(renderer, texture, &portion, &l_renderLocation, parent->GetTransform().angle, nullptr, SDL_FLIP_NONE);
}

void ACE_Texture2D::FreeTexture()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		texWidth = 0;
		texHeight = 0;
	}   
}
