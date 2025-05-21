#pragma once
#include <functional>

#include "Objects/ACE_Object.h"
#include "SDL3/SDL.h"

class ACE_WindowManager : public ACE_Object
{
public:
	~ACE_WindowManager() override;
	static ACE_WindowManager* Instance();
	
	bool CreateWindow();
	void CloseWindow();
	
	SDL_Renderer* GetRenderer() const { return renderer; }
	SDL_Window* GetWindow() const { return window; }

	void Update(std::function<void(float, SDL_Event)> callback, float deltaTime, SDL_Event event);
	void Render(std::function<void(SDL_Renderer*)> callback, SDL_Renderer* renderer);
	
private:
	ACE_WindowManager() = default;
	static ACE_WindowManager* instance;
	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const char* initTitle = "ACEngine";
};
