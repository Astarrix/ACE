#include "ACE_UIElement.h"

#include "Objects/Managers/ACE_EventSystem.h"

void ACE_UIElement::Update(float deltaTime, SDL_Event event)
{
	ACE_Object::Update(deltaTime, event);
	switch (event.type)
	{
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			ACE_Vector2D mousePos = ACE_Vector2D(event.button.x, event.button.y);
			if (localBounds.Contains(mousePos))
			{
				if (!isClicked)
				{
					isClicked = true;
					ACE_Event clickEvent =
						{
							ACE_EventType::UI
									
						};
				}
			}
		}
		break;
	case SDL_EVENT_MOUSE_MOTION:
		{
			ACE_Vector2D mousePos = ACE_Vector2D(event.motion.x, event.motion.y);
			if (localBounds.Contains(mousePos))
			{
				if (!isHovered) {isHovered = true;}
			}
			else
			{
				isHovered = false;
			}
		}
		break;
	case SDL_EVENT_MOUSE_BUTTON_UP:
		if (isClicked)
		{
			isClicked = false;
		}
		break;
	}
}
