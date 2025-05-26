#include "ACE_CollisionManager.h"

#include "Objects/Actors/ACE_Actor.h"

ACE_CollisionManager* ACE_CollisionManager::instance = nullptr;

ACE_CollisionManager::~ACE_CollisionManager()
{
	instance = nullptr;
}

ACE_CollisionManager* ACE_CollisionManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ACE_CollisionManager();
	}
	return instance;
}

bool ACE_CollisionManager::CheckCollision(ACE_Actor* body1, ACE_Actor* body2)
{
	return body1->GetBoundingBox().Overlaps(body2->GetBoundingBox());
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

void ACE_CollisionManager::AddActor(ACE_Actor* actor)
{
	actors.push_back(actor);
}

void ACE_CollisionManager::RemoveActor(ACE_Actor* actor)
{
	auto it = std::find(actors.begin(), actors.end(), actor);
	if (it != actors.end())
	{
		actors.erase(it);
	}
}

void ACE_CollisionManager::CheckAllCollisions()
{
	for (size_t i = 0; i < actors.size(); i++)
	{
		for (size_t j = i + 1; j < actors.size(); j++)
		{
			if (CheckCollision(actors[i], actors[j]))
			{
				ResolveCollision(actors[i], actors[j]);
				if (actors[i]->generateHitEvents && actors[j]->generateHitEvents)
				{
					HitData hit =
						{
						.body1 = actors[i],
						.body2 = actors[j]
						};

					ACE_Event HitEvent
					{
						ACE_EventType::Collision,
						&hit,
						nullptr,
						nullptr,
						""
					};
				
					ACE_EventSystem::Instance()->Dispatch(HitEvent);
				}
			}
		}
	}
}

void ACE_CollisionManager::ResolveCollision(ACE_Actor* actor1, ACE_Actor* actor2)
{
	ACE_Box2D bounds1 = actor1->GetBoundingBox();
	ACE_Box2D bounds2 = actor2->GetBoundingBox();

	float overlapWidth = std::min(bounds1.x + bounds1.width, bounds2.x + bounds2.width) - std::max(bounds1.x, bounds2.x);
	float overlapHeight = std::min(bounds1.y + bounds1.height, bounds2.y + bounds2.height) - std::max(bounds1.y, bounds2.y);

	if (overlapWidth < overlapHeight)
	{
		//actor1->SetPosition(LeftOfOverlap);
		if (actor1->GetPosition().x < actor2->GetPosition().x)
		{
			// actor 1 is hitting left wall of actor 2

			ACE_Vector2D LeftOfOverlap = ACE_Vector2D(actor1->GetPosition().x - overlapWidth / 2, actor1->GetPosition().y);
			ACE_Vector2D RightOfOverlap = ACE_Vector2D(actor2->GetPosition().x + overlapWidth / 2, actor2->GetPosition().y);

			if (!actor1->isStaticMove)
			{
				actor1->SetPosition(LeftOfOverlap);
				float clampedX = actor1->GetVelocity().x > 0.0f ? 0.0f : actor1->GetVelocity().x;
				actor1->SetVelocity(ACE_Vector2D(clampedX, actor1->GetVelocity().y));	
			}
			if (!actor2->isStaticMove)
			{
				actor2->SetPosition(RightOfOverlap);
				float clampedX = actor2->GetVelocity().x < 0.0f ? 0.0f : actor2->GetVelocity().x;
				actor2->SetVelocity(ACE_Vector2D(clampedX, actor2->GetVelocity().y));
			}
		}
		else
		{
			// actor 1 is hitting right wall of actor 2

			ACE_Vector2D LeftOfOverlap = ACE_Vector2D(actor2->GetPosition().x - overlapWidth / 2, actor2->GetPosition().y);
			ACE_Vector2D RightOfOverlap = ACE_Vector2D(actor1->GetPosition().x + overlapWidth / 2, actor1->GetPosition().y);

			if (!actor1->isStaticMove)
			{
				actor1->SetPosition(RightOfOverlap);
				float clampedX = actor1->GetVelocity().x < 0.0f ? 0.0f : actor1->GetVelocity().x;
				actor1->SetVelocity(ACE_Vector2D(clampedX, actor1->GetVelocity().y));
			}
			if (!actor2->isStaticMove)
			{
				actor2->SetPosition(LeftOfOverlap);
				float clampedX = actor2->GetVelocity().x > 0.0f ? 0.0f : actor2->GetVelocity().x;
				actor2->SetVelocity(ACE_Vector2D(clampedX, actor2->GetVelocity().y));
			}
		}
	}
	else
	{
		// Resolve vertical collision
		if (actor1->GetPosition().y < actor2->GetPosition().y)
		{
			// actor 1 is landing on the top of actor 2

			ACE_Vector2D AboveOverlap = ACE_Vector2D(actor1->GetPosition().x, actor1->GetTransform().position.y - overlapHeight / 2 - 0.5);
			ACE_Vector2D BelowOverlap = ACE_Vector2D(actor2->GetPosition().x, actor2->GetTransform().position.y + overlapHeight / 2);

			if (!actor1->isStaticMove)
			{
				actor1->SetPosition(AboveOverlap);
				actor1->SetIsGrounded(true);
				//std::cout << actor1->friendlyName << " is Grounded" << std::endl;
				float clampedY = actor1->GetVelocity().y < 0.0f ? actor1->GetVelocity().y : 0.0f; // can jump cant fall
				actor1->SetVelocity(ACE_Vector2D(actor1->GetVelocity().x, clampedY));
			}
			if (!actor2->isStaticMove)
			{
				actor2->SetPosition(BelowOverlap);
				float clampedY = actor2->GetVelocity().y > 0.0f ? actor2->GetVelocity().y : 0.0f; // cant jump can fall
				actor2->SetVelocity(ACE_Vector2D(actor2->GetVelocity().x, clampedY));
			}
			//std::cout << "actor1: " << actor1->friendlyName << " is hitting the top of " << actor2->friendlyName << std::endl;
		}
		else
		{
			// actor 1 is hitting the bottom of actor 2

			ACE_Vector2D AboveOverlap = ACE_Vector2D(actor2->GetPosition().x, actor2->GetTransform().position.y - overlapHeight / 2 - 0.5);
			ACE_Vector2D BelowOverlap = ACE_Vector2D(actor1->GetPosition().x, actor1->GetTransform().position.y + overlapHeight / 2);

			if (!actor1->isStaticMove)
			{
				// cant jump can fall
				actor1->SetPosition(BelowOverlap);
				float clampedY = actor1->GetVelocity().y > 0.0f ? actor1->GetVelocity().y : 0.0f;
				actor1->SetVelocity(ACE_Vector2D(actor1->GetVelocity().x, clampedY));
			}
			if (!actor2->isStaticMove)
			{
				// can jump cant fall
				actor2->SetPosition(AboveOverlap);
				actor2->SetIsGrounded(true);
				//std::cout << actor2->friendlyName << " is Grounded - " << std::endl;
				float clampedY = actor2->GetVelocity().y < 0.0f ? actor2->GetVelocity().y : 0.0f;
				actor2->SetVelocity(ACE_Vector2D(actor2->GetVelocity().x, clampedY));
			}
			//std::cout << "actor2: " << actor2->friendlyName << " is on top of " << actor1->friendlyName << std::endl;
		}
	}
}
