#include "CollisionManager.h"
#include "Player2D.h"
#include "Collectables.h"

#include <iostream>

void CollisionManager::checkCollision(Room* room)
{
	bool collided = false;
	//cycle through all game objects
	for each (GameObject2D* obj in room->getColldingObjects())
	{
		//if the player collides with collider
		if (room->getPlayer()->checkCollisions(obj))
		{
			if ((obj)->GetType() != ObjectType::PLAYER)
			{
				//Do collision behaviour
				resolveCollision(room, obj);
				collided = true;
			}
		}
	}

	if (!collided)
	{
		room->getPlayer()->SetIsGrounded(false);
		room->getPlayer()->setOnLadder(false);
	}
}

bool CollisionManager::isCollided(GameObject2D* gameObject1, GameObject2D* gameObject2)
{
	return gameObject1->checkCollisions(gameObject2);
}

void CollisionManager::resolveCollision(Room* room, GameObject2D* obj)
{
	switch (obj->GetType())
	{
	case ObjectType::COLLECTIBLE:
		if (!room->getCollectable()->GetPickedUp())
		{
			std::cout << "Collected \n";
			room->getPlayer()->addCollectable();
			obj->SetAlive(false);
			room->getCollectable()->SetPickeduP();
		}
		break;
	case ObjectType::ENEMY:
		if (room->getPlayer()->getLives() != 0)
		{
			room->getPlayer()->SetAlive(false);
			room->getPlayer()->TakeLives();
			
			if (room->getRespawner()->GetRespawnUp())
			{
				room->getPlayer()->SetAlive(true);
				room->getPlayer()->SetPos(room->getRespawner()->GetPos());
				room->getPlayer()->SetPlayerState(PlayerState::PlayerState_IDLE);
			}
			else
			{
				room->getPlayer()->SetAlive(true);
				room->getPlayer()->SetPos(Vector2(200, 450));
			}
			room->getPlayer()->SetZeroVel(0);
		}
		else
		{
			room->getPlayer()->SetAlive(false);
		}
		break;
	case ObjectType::LADDER:
		break;
	case ObjectType::PLATFORM:
		if (room->getPlayer()->GetPlayerState() != PlayerState::PlayerState_JUMP)
		{
			room->getPlayer()->SetIsGrounded(true);
			room->getPlayer()->SetSpeedY(0.0f);
		}
		if (room->getPlayer()->GetVel().y < obj->GetPos().y)
		{
			//top collision
			room->getPlayer()->SetIsGrounded(true);
			room->getPlayer()->SetSpeedY(0.0f);
		}
		else if (room->getPlayer()->GetPos().y > obj->GetPos().y)
		{
			//bottom collision
			room->getPlayer()->SetSpeedY(0.0f);
		}
		break;
	case ObjectType::RESPAWN:
		room->getRespawner()->SetRespawnUp(true);
		break;
	}
}
