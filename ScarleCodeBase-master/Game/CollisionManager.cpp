#include "CollisionManager.h"
#include "Room.h"

void CollisionManager::checkCollision(std::list<GameObject2D*> go, Room* room)
{
	//find the player in the list of gameobjects
	for (list<GameObject2D*>::iterator player = room->getColldingObjects().begin();
		player != room->getColldingObjects().end(); player++)
	{
		if ((*player)->GetType() == ObjectType::PLAYER)
		{
			for (list<GameObject2D*>::iterator collider = room->getColldingObjects().begin(); 
				collider != room->getColldingObjects().end(); collider++)
			{

			}
		}
	}
}

bool CollisionManager::isCollided(GameObject2D* gameObject1, GameObject2D* gameObject2)
{
	return false;
}

void CollisionManager::resolveCollision()
{
}
