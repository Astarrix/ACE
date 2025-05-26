#pragma once
#include "Commons/ACE_Box2D.h"
#include "Commons/ACE_Circle2D.h"
#include "Objects/Managers/ACE_EventSystem.h"

class ACE_Actor;

struct HitData
{
	ACE_Actor* body1;
	ACE_Actor* body2;
};


class ACE_CollisionManager
{
public:
	~ACE_CollisionManager();
	static ACE_CollisionManager* getInstance();

	void AddActor(ACE_Actor* actor);
	void RemoveActor(ACE_Actor* actor);
	void CheckAllCollisions();

	static bool CheckCollision(ACE_Actor* body1, ACE_Actor* body2);
	static bool CheckCollision(ACE_Circle2D circle1, ACE_Circle2D circle2);
	static bool CheckCollision(ACE_Box2D box1, ACE_Box2D box2);

private:
	ACE_CollisionManager();
	static ACE_CollisionManager* instance;
	std::vector<ACE_Actor*> actors;
	void ResolveCollision(ACE_Actor* actor1, ACE_Actor* actor2);
};
