#include "CollisionManager.h"
#include "Characters/Character.h"

CollisionManager* CollisionManager::instance = nullptr;
CollisionManager::~CollisionManager()
{
	instance = nullptr;
}

CollisionManager* CollisionManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new CollisionManager();
	}
	return instance;
}

bool CollisionManager::CheckCollision(Character* character1, Character* character2)
{
	return character1->GetBoundingBox().Overlaps(character2->GetBoundingBox());
}

bool CollisionManager::CheckCollision(Circle2D circle1, Circle2D circle2)
{
	return circle1.Overlaps(circle2);
}

bool CollisionManager::CheckCollision(Box2D box1, Box2D box2)
{
	return box1.Overlaps(box2);
}

CollisionManager::CollisionManager()
{
}
