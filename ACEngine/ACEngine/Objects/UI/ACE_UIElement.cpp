#include "ACE_UIElement.h"

#include "Objects/Managers/ACE_EventSystem.h"

void ACE_UIElement::Render()
{ //TODO
	for (ACE_UIElement* elem : children)
	{
		elem->Render();
	}
}

void ACE_UIElement::Init()
{
	ACE_Object::Init();
	for (ACE_UIElement* elem : children)
	{
		elem->Init();
	}
}

void ACE_UIElement::SetScreenPosition(ACE_Vector2D newPosition)
{
	screenBounds.Move(newPosition);
}

void ACE_UIElement::SetLocalPosition(ACE_Vector2D newPosition)
{
	if (parent)
	{
		SetScreenPosition(parent->GetScreenPosition() + newPosition);
	}
	else
	{
		SetScreenPosition(newPosition);
	}
}

ACE_Vector2D ACE_UIElement::GetLocalPosition()
{
	if (parent)
	{
		return parent->GetScreenPosition() - GetScreenPosition();
	}
	return GetScreenPosition();
}

void ACE_UIElement::SetVisibility(ACE_UIVISIBILITYTYPE newVisibility)
{
	visibility = newVisibility;
}

ACE_UIVISIBILITYTYPE ACE_UIElement::GetVisibility() const
{
	return visibility;
}

void ACE_UIElement::OnClick()
{ //TODO
}

void ACE_UIElement::OnHover()
{ //TODO
}

void ACE_UIElement::OnUnhover()
{ //TODO
}

void ACE_UIElement::AddChild(ACE_UIElement* child)
{
	child->parent = this;
	children.push_back(child);
}

void ACE_UIElement::RemoveChild(ACE_UIElement* child)
{
}

void ACE_UIElement::Update(float deltaTime, SDL_Event event)
{
	ACE_Object::Update(deltaTime, event);
	switch (event.type)
	{
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			ACE_Vector2D mousePos = ACE_Vector2D(event.button.x, event.button.y);
			if (screenBounds.Contains(mousePos))
			{
				if (!isClicked)
				{
					isClicked = true;
					ACE_Event clickEvent =
					{
						ACE_EventType::UI,
						(ACE_Object*)this
					};
					ACE_EventSystem::Instance()->Dispatch(clickEvent);
				}
			}
		}
		break;
	case SDL_EVENT_MOUSE_MOTION:
		{
			ACE_Vector2D mousePos = ACE_Vector2D(event.motion.x, event.motion.y);
			if (screenBounds.Contains(mousePos))
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
	for (ACE_UIElement* elem : children)
	{
		elem->Update(deltaTime, event);
	}
}
