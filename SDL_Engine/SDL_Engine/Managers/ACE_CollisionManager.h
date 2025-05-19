#pragma once

#include "Commons/ACE_Box2D.h"
#include "Commons/ACE_Circle2D.h"

class Character;

class ACE_CollisionManager
{
public:
	~ACE_CollisionManager();
	static ACE_CollisionManager* Instance();
	bool CheckCollision(Character* character1, Character* character2);
	bool CheckCollision(ACE_Circle2D circle1, ACE_Circle2D circle2);
	bool CheckCollision(ACE_Box2D box1, ACE_Box2D box2);
private:
	ACE_CollisionManager();
	static ACE_CollisionManager* instance;
};
