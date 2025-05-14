#pragma once

#include "commons/Box2D.h"
#include "commons/Circle2D.h"

class Character;

class CollisionManager
{
public:
	~CollisionManager();
	static CollisionManager* Instance();
	bool CheckCollision(Character* character1, Character* character2);
	bool CheckCollision(Circle2D circle1, Circle2D circle2);
	bool CheckCollision(Box2D box1, Box2D box2);
private:
	CollisionManager();
	static CollisionManager* instance;
};
