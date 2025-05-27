#pragma once
#include <vector>

#include "Commons/ACE_Box2D.h"
#include "Objects/ACE_Object.h"
#include "Objects/Components/Sub-Components/ACE_Sprite2D.h"

enum ACE_UIVISIBILITYTYPE
{
	HIDDEN,
	INTERACTIBLE,
	RENDERED,
};

class ACE_UIElement : ACE_Object
{
public:
	void Render();
	void Init() override;
	void Update(float deltaTime, SDL_Event event) override;
	void SetScreenPosition(ACE_Vector2D newPosition);
	void SetLocalPosition(ACE_Vector2D newPosition);
	ACE_Vector2D GetScreenPosition() const { return {screenBounds.x, screenBounds.y}; }
	ACE_Vector2D GetLocalPosition();
	void SetVisibility(ACE_UIVISIBILITYTYPE newVisibility);
	ACE_UIVISIBILITYTYPE GetVisibility() const;

protected:
	virtual void OnClick();
	virtual void OnHover();
	virtual void OnUnhover();
	void AddChild(ACE_UIElement* child);
	void RemoveChild(ACE_UIElement* child);

private:
	ACE_Box2D screenBounds;
	ACE_UIElement* parent = nullptr;
	std::vector<ACE_UIElement*> children;
	ACE_UIVISIBILITYTYPE visibility = RENDERED;
	int zOrder = 0;
	bool isHovered = false;
	bool isClicked = false;
};
