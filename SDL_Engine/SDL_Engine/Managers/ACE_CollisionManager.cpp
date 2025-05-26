#include "ACE_CollisionManager.h"
#include "Characters/Character.h"

ACE_CollisionManager* ACE_CollisionManager::instance = nullptr;
ACE_CollisionManager::~ACE_CollisionManager()
{
	instance = nullptr;
}

ACE_CollisionManager* ACE_CollisionManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new ACE_CollisionManager();
	}
	return instance;
}

bool ACE_CollisionManager::CheckCollision(Character* character1, Character* character2)
{
	return character1->GetBoundingBox().Overlaps(character2->GetBoundingBox());
}

bool ACE_CollisionManager::CheckCollision(ACE_Circle2D circle1, ACE_Circle2D circle2)
{
	return circle1.Overlaps(circle2);
}

bool ACE_CollisionManager::CheckCollision(ACE_Box2D box1, ACE_Box2D box2)
{
	return box1.Overlaps(box2);
}
	
ACE_CollisionManager::ACE_CollisionManager()
{
}
