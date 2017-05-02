#include "CollisionManager.h"
#include "Player2D.h"
#include "Collectables.h"
#include "Tile.h"
#include "Enemy.h"
#include "MotherObstecle.h"


#include <iostream>

void CollisionManager::checkCollision(Room* room)
{
	bool collided = false;
	//cycle through all game objects
	for each (GameObject2D* obj in room->getColldingObjects())
	{
		//if the player collides with collider
		if (isCollided(room->getPlayer(), obj))
		{
			if (room->getPlayer()->isAlive())
			{
				if ((obj)->GetType() != ObjectType::PLAYER)
				{
					Direction dir;
					dir = checkDirection(room->getPlayer(), obj);
					//Do collision behaviour
					resolveCollision(room, obj, dir);
					collided = true;
				}
			}
		}
	}

	//if nothing collides
	if (!collided)
	{
		room->getPlayer()->SetIsGrounded(false);
		room->getPlayer()->setOnLadder(false);
	}
}

bool CollisionManager::isCollided(GameObject2D* gameObject1, GameObject2D* gameObject2)
{
	//downcast the player object
	Player2D* player = dynamic_cast<Player2D*> (gameObject1);

	//check if gameObject 2 is a tile
	if (dynamic_cast<Tile*> (gameObject2) != NULL)
	{
		Tile* tile = dynamic_cast<Tile*>  (gameObject2);
		
		if ((tile->getSprite()->getSpriteHeight() * tile->getScale().y) + tile->GetPos().y >= player->getSprite()->GetPos().y &&
			tile->GetPos().y <= player->GetPos().y + (player->getSprite()->getSpriteHeight() * player->getScale().y) &&
			(tile->getSprite()->getSpriteWidth() * tile->getScale().x) + tile->GetPos().x >= player->GetPos().x &&
			tile->GetPos().x <= (player->getSprite()->getSpriteWidth() * player->getScale().x) + player->GetPos().x)
		{
			return true;
		}
	}
	//check if gameObject2 is a collectable
	else if (dynamic_cast<Collectables*> (gameObject2) != NULL)
	{
		Collectables* collect = dynamic_cast<Collectables*> (gameObject2);

		if ((collect->getSprite()->getSpriteHeight() * collect->getScale().y) + collect->GetPos().y >= player->getSprite()->GetPos().y &&
			collect->GetPos().y <= player->GetPos().y + (player->getSprite()->getSpriteHeight() * player->getScale().y) &&
			(collect->getSprite()->getSpriteWidth() * collect->getScale().x) + collect->GetPos().x >= player->GetPos().x &&
			collect->GetPos().x <= (player->getSprite()->getSpriteWidth() * player->getScale().x) + player->GetPos().x)
		{
			if (collect->isAlive())
			{
				return true;
			}
		}
	}
	//check if gameObject2 is an Enemy
	else if (dynamic_cast<Enemy*> (gameObject2) != NULL)
	{
		Enemy* enemy = dynamic_cast<Enemy*> (gameObject2);

		if ((enemy->getSprite()->getSpriteHeight() * enemy->getScale().y) + enemy->GetPos().y >= player->getSprite()->GetPos().y &&
			enemy->GetPos().y <= player->GetPos().y + (player->getSprite()->getSpriteHeight() * player->getScale().y) &&
			(enemy->getSprite()->getSpriteWidth() * enemy->getScale().x) + enemy->GetPos().x >= player->GetPos().x &&
			enemy->GetPos().x <= (player->getSprite()->getSpriteWidth() * player->getScale().x) + player->GetPos().x)
		{
			return true;
		}
	}
	else if (dynamic_cast<MotherObstacle*> (gameObject2) != NULL)
	{
		MotherObstacle* mother = dynamic_cast<MotherObstacle*> (gameObject2);

		if ((mother->getSprite()->getSpriteHeight() * mother->getScale().y) + mother->GetPos().y >= mother->getSprite()->GetPos().y &&
			mother->GetPos().y <= player->GetPos().y + (player->getSprite()->getSpriteHeight() * player->getScale().y) &&
			(mother->getSprite()->getSpriteWidth() * mother->getScale().x) + mother->GetPos().x >= player->GetPos().x &&
			mother->GetPos().x <= (player->getSprite()->getSpriteWidth() * player->getScale().x) + player->GetPos().x)
		{
			return true;
		}

	}
	
	//return false if the other object does not collide anything
	return false;
}

void CollisionManager::resolveCollision(Room* room, GameObject2D* obj, Direction direction)
{
	//Ladder collisions overider everything
	if (obj->GetType() == ObjectType::LADDER)
	{
		room->getPlayer()->SetIsGrounded(true);
		room->getPlayer()->setHasJumped(false);
		room->getPlayer()->SetSpeedY(0.0f);
		room->getPlayer()->setOnLadder(true);
	}
	else
	{
		//Switch statement to check other objects
		switch (obj->GetType())
		{
		case ObjectType::COLLECTIBLE:
			if (obj->isAlive())
			{
				std::cout << "Collected \n";
				room->getPlayer()->addCollectable();
				obj->SetAlive(false);
			}
			break;
		case ObjectType::CONVEYORLEFT:
		{
			if (room->getPlayer()->GetPlayerState() != PlayerState::PlayerState_JUMP)
			{
				room->getPlayer()->SetIsGrounded(true);
				room->getPlayer()->SetSpeedY(0.0f);

				float currentPosX = room->getPlayer()->GetPos().x;
				float currentPosY = room->getPlayer()->GetPos().y;
				room->getPlayer()->SetPos(Vector2(currentPosX - 0.05, currentPosY));
				room->getPlayer()->setfriction(0.046875 * 40);

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
		}
		break;
		case ObjectType::CONVEYORRIGHT:
		{
			if (room->getPlayer()->GetPlayerState() != PlayerState::PlayerState_JUMP)
			{
				room->getPlayer()->SetIsGrounded(true);
				room->getPlayer()->SetSpeedY(0.0f);

				float currentPosX = room->getPlayer()->GetPos().x;
				float currentPosY = room->getPlayer()->GetPos().y;
				room->getPlayer()->SetPos(Vector2(currentPosX + 0.05, currentPosY));
				room->getPlayer()->setfriction(0.046875 * 40);

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
		}
		break;
		case ObjectType::ICE:
		{
			if (room->getPlayer()->GetPlayerState() != PlayerState::PlayerState_JUMP)
			{
				room->getPlayer()->SetIsGrounded(true);
				room->getPlayer()->SetSpeedY(0.0f);

				room->getPlayer()->setfriction(0.046875 * 25);
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
					room->getPlayer()->SetPos(room->getPlayerSpawn());
				}
				room->getPlayer()->SetZeroVel(0);
			}
			else
			{
				room->getPlayer()->SetAlive(false);
			}
			break;
		case ObjectType::MOTHER:
			if (room->getPlayer()->getCollectables() != 3)
			{


				if (room->getPlayer()->GetPos().x > obj->GetPos().x + 40 &&
					room->getPlayer()->GetPos().y <= obj->GetPos().y + 50
					&& room->getPlayer()->GetPos().y >= obj->GetPos().y - 50)
				{
					//right collision
					float currentY = room->getPlayer()->GetPos().y;

					room->getPlayer()->SetPos(Vector2(obj->GetPos().x + 55, currentY));
					room->getPlayer()->SetSpeed(0);


				}
				else if (room->getPlayer()->GetPos().x >= obj->GetPos().x - 40 &&
					room->getPlayer()->GetPos().y < obj->GetPos().y + 50
					&& room->getPlayer()->GetPos().y >= obj->GetPos().y - 50)
				{
					//left collision

					float currentY = room->getPlayer()->GetPos().y;
					room->getPlayer()->SetPos(Vector2(obj->GetPos().x - 40, currentY));
					room->getPlayer()->SetSpeed(0);

				}
				if (room->getPlayer()->GetPos().y <= obj->GetPos().y - 50)
				{
					//bottom collision
					float currentX = room->getPlayer()->GetPos().x;
					room->getPlayer()->SetPos(Vector2(currentX, obj->GetPos().y - 40));
					room->getPlayer()->SetSpeedY(0);
				}

				else if (room->getPlayer()->GetPos().y >= obj->GetPos().y + 50 &&
					room->getPlayer()->GetPos().y <= obj->GetPos().y + 50)
				{
					//top collision
					float currentX = room->getPlayer()->GetPos().x;
					room->getPlayer()->SetPos(Vector2(currentX, obj->GetPos().y + 40));
					room->getPlayer()->SetSpeedY(0);
				}
			}
			else
			{
				//PLAYER WINS - STATE CHANGE TO WIN/GAME OVER
				room->getMother()->setBlocking(false);
			}
			break;
		case ObjectType::PLATFORM:
			//If the player is above the platform

			if (dynamic_cast<Tile*> (obj) != NULL)
			{
				Tile* _plat = dynamic_cast<Tile*> (obj);
				//Top Collision
				if (direction == Direction::TOP)
				{
					room->getPlayer()->SetSpeedY(-10);
					room->getPlayer()->SetIsGrounded(true);
				}
				//Bot Collision
				if (direction == Direction::BOTTOM)
				{

				}
				//left Collision 
				if (direction == Direction::LEFT && room->getPlayer()->getIsGrounded())
				{
					room->getPlayer()->SetSpeed(-200);
				}
				//Right Collision
				if (direction == Direction::RIGHT && room->getPlayer()->getIsGrounded())
				{
					room->getPlayer()->SetSpeed(+200);
					//_plat->SetColour(Color(0, 1, 0, 1));
				}
			}
			break;
		case ObjectType::RESPAWN:
			room->getRespawner()->SetRespawnUp(true);
			break;
		}
	}
}

Direction CollisionManager::checkDirection(GameObject2D* obj1, GameObject2D* obj2)
{
	if (dynamic_cast<Player2D*> (obj1) != NULL)
	{
		Player2D* player = dynamic_cast<Player2D*> (obj1);

		if (dynamic_cast<Tile*> (obj2) != NULL)
		{
			Tile* tile = dynamic_cast<Tile*>  (obj2);

			float playerBot = player->GetPos().y + (player->getSprite()->getSpriteHeight() * player->getScale().y);
			float playerRight = player->GetPos().x + (player->getSprite()->getSpriteWidth() * player->getScale().x);

			float platBot = tile->GetPos().y + (tile->getSprite()->getSpriteHeight() * tile->getScale().y);
			float platRight = tile->GetPos().x + (tile->getSprite()->getSpriteWidth() * tile->getScale().x);


			float botCollision = platBot - player->GetPos().y;
			float topCollision = playerBot - tile->GetPos().y;
			float leftCollision = playerRight - tile->GetPos().x;
			float rightCollision = platRight - player->GetPos().x;

			//Top Collision
			if (topCollision < botCollision &&
				topCollision < leftCollision &&
				topCollision < rightCollision)
			{
				return Direction::TOP;
			}

			//Bot Collision
			if (botCollision < topCollision &&
				botCollision < leftCollision &&
				botCollision < rightCollision)
			{
				return Direction::BOTTOM;
			}

			//left Collision 
			if (leftCollision < rightCollision &&
				leftCollision < topCollision &&
				leftCollision < botCollision)
			{
				return Direction::LEFT;
			}

			//Right Collision
			if (rightCollision < leftCollision &&
				rightCollision < topCollision &&
				rightCollision < botCollision)
			{
				return Direction::RIGHT;
			}
		}
	}
}
