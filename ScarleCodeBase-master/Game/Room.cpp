#include "Room.h"
#include "Levels.h"
#include "gamedata.h"

#include "Sprite.h"

#include "Tile.h"
#include "Player2D.h"
#include "Collectables.h"
#include "Enemy.h"
#include "MotherObstecle.h"

#include "CameraFollow2D.h"

#include <sstream>
#include<Windows.h>

Room::Room(Levels& L) :
	level(L)
{
	title = L.getTitle();
	map =L.getMap();

	plat = nullptr;
	ladder = nullptr;
	//player = nullptr;
	pickUp = nullptr;
	respawner = nullptr;
	enemyHor = nullptr;
	mother = nullptr;
	conveyorLeft = nullptr;
	conveyorRight = nullptr;
	ice = nullptr;
	firstLevel = true;
	levelIncrease = false;
	LevelDecrease = false;

	
	for (int i = 0; i < L.LoadedLevels.size(); i++)
	{
		preLevels.push_back(InSceneObjects);
	}

}

list<GameObject2D*> Room::getColldingObjects()
{
	 return m_collider; 
}

void Room::CreateRoom(GameData* _GD, ID3D11Device* _pd3dDevice)
{
	
	Vector2 TilePos(0, 0);  //x and y coordiantes of Tiles to be placed

	Sprite* _platform = new Sprite("Platform", _pd3dDevice);
	Sprite* _ladder = new Sprite("Ladder", _pd3dDevice);
	Sprite* _collectable = new Sprite("Collectable", _pd3dDevice);
	Sprite* _respawn = new Sprite("CheckPoint", _pd3dDevice);
	Sprite* _doorEnt = new Sprite("Door", _pd3dDevice);
	Sprite* _enemyHor = new Sprite("EnemyHor", _pd3dDevice);
	Sprite* _motherObstacle = new Sprite("motherFigure", _pd3dDevice);
	Sprite* _conveyerBelt = new Sprite("ConveyerBelt", _pd3dDevice);
	Sprite* _ice = new Sprite("Ice", _pd3dDevice);

	bool makeCollectable = true;

	for (auto&& mapRow : map)
	{
		for (int i = 0; i < mapRow.size(); i++)
		{
			if (TilePos.x >= (_GD->viewportWidth*2))
			{
			TilePos.x = 0;
			TilePos.y += incrementer.y*0.5;//needs to be change to size of tile
			}
			switch (mapRow.at(i))
			{
			case '_':
				//create a platfrom;
				
				plat = new Tile(_platform, TilePos);
				plat->setType(PLATFORM);

				InSceneObjects.push_back(plat);
				m_collider.push_back(plat);
				break;
			case'I':
				//invisible wall

				invisPlat = new Tile(_platform, TilePos);
				//invisPlat->SetRot(150.0f);//set rotation or set width plus height when functionailty is in there 
				//invisPlat->SetAlive(false);
				invisPlat->setType(PLATFORM);
				InSceneObjects.push_back(invisPlat);
				m_collider.push_back(invisPlat);

				incrementer = Vector2(invisPlat->getSprite()->getSpriteWidth(), invisPlat->getSprite()->getSpriteHeight());
				break;


			case'H':
				//create ladderTile
				ladder = new Tile(_ladder, TilePos);
				ladder->setType(ObjectType::LADDER);
				InSceneObjects.push_back(ladder);
				m_collider.push_back(ladder);
				break;

			case'|':
				//Rope Tile depending on how it wil work will go here

				//RopeTile = new Rope(_Rope, TilePos);
				//InSceneObjects.push_back(RopeTile);
				//m_collider.push_back(RopeTile);
				break;

			case'*':
				// create player 
				// create player 
				if (player == nullptr)
				{
					player = new Player2D("Walk", _pd3dDevice);
					player->SetScale(1.0f);
					player->SetPos(TilePos);
					Playerspawn = TilePos;
					player->setType(PLAYER);
				}

				InSceneObjects.push_back(player);
				m_collider.push_back(player);

				m_playerCam = new CameraFollow2D(player);
				InSceneObjects.push_back(m_playerCam);

				break;

			case'$':
				//create collecatable
				
				makeCollectable = true;
				pickUp = new Collectables(_collectable);
				pickUp->SetPos(TilePos);
				InSceneObjects.push_back(pickUp);
				m_collider.push_back(pickUp);

				for (auto prevColl : preLevels[levelCur])// for every object previously stored in this level
				{
					if (prevColl->GetType() == COLLECTIBLE)//is there a collectable in this level
					{
						if (prevColl->GetPos() == TilePos)// is this the same collectable 
						{
							if (!prevColl->isAlive())// was this collectable dead when they left 
							{
								pickUp->SetAlive(false);
							}
						}

					}
				}
				/*if (makeCollectable)
				{
					pickUp = new Collectables(_collectable);
					pickUp->SetPos(TilePos);
					pickUp->SetAlive(true);
					InSceneObjects.push_back(pickUp);
					m_collider.push_back(pickUp);
				}*/
				break;

			case '@':
				respawner = new Collectables(_respawn);
				respawner->SetScale(0.5f);
				respawner->SetPos(TilePos);
				respawner->SetAlive(true);
				InSceneObjects.push_back(respawner);
				respawner->setType(RESPAWN);
				m_collider.push_back(respawner);
				break;

			case 'E':

				Exit = new Collectables(_doorEnt);
				Exit->SetScale(0.5f);
				Exit->SetPos(TilePos);
				Exit->SetAlive(true);
				Exit->setType(DOOREXIT);

				InSceneObjects.push_back(Exit);
				m_collider.push_back(Exit);
				break;
			case 'D':

				Entrance = new Collectables(_doorEnt);
				Entrance->SetScale(0.5f);
				Entrance->SetPos(TilePos);
				Entrance->SetAlive(true);
				Entrance->setType(DOORENT);

				InSceneObjects.push_back(Entrance);
				m_collider.push_back(Entrance);

				break;

			case '+':
				enemyStartPos = TilePos;
				break;

			case'%':
				//create enemy
				enemyHor = new Enemy(_enemyHor, enemyStartPos, TilePos);

				InSceneObjects.push_back(enemyHor);
				m_collider.push_back(enemyHor);

				break;
			case 'm':
				
					//create motherObstecle
					mother = new MotherObstacle(_motherObstacle, TilePos);
					InSceneObjects.push_back(mother);
					m_collider.push_back(mother);
					break;
			case '<':

				conveyorLeft = new Tile(_conveyerBelt, TilePos);
				conveyorLeft->setType(ObjectType::CONVEYORLEFT);
				//conveyorLeft->SetScale(0.05f);
				InSceneObjects.push_back(conveyorLeft);
				m_collider.push_back(conveyorLeft);
				break;
			case '>':

				conveyorRight = new Tile(_conveyerBelt, TilePos);
				conveyorRight->setType(ObjectType::CONVEYORRIGHT);
				//conveyorRight->SetScale(0.05f);
				InSceneObjects.push_back(conveyorRight);
				m_collider.push_back(conveyorRight);
				break;
			case '!':
				ice = new Tile(_ice, TilePos);
				ice->setType(ObjectType::ICE);
				//ice->SetScale(0.05f);
				InSceneObjects.push_back(ice);
				m_collider.push_back(ice);
			case '-':
				thinPlat = new Tile(_platform, TilePos);
				thinPlat->setType(ObjectType::THINPLATFORM);

				InSceneObjects.push_back(thinPlat);
				m_collider.push_back(thinPlat);
			default:
				break;
			}
			TilePos.x += 30;//Tilesize
		}
	}
	preLevels[levelCur] = InSceneObjects;
}

void Room::setCurrentLevel(int i)
{
	levelCur = i;
}

void Room::Tick(GameData* _GD)
{
	for (auto& Object : InSceneObjects)
	{
		Object->Tick(_GD);
	}
}

void Room::Draw(DrawData2D* _DD)
{
	for (auto& Object : InSceneObjects)
	{
		if (Object->isAlive())
		{
			Object->Draw(_DD);
		}
	}
}

void Room::setCollectableAlive()
{
	for (auto& Object : InSceneObjects)
	{
		if (Object->GetType() == ObjectType::COLLECTIBLE)
		{
			Object->SetAlive(true);
		}
		if (Object->GetType() == ObjectType::RESPAWN)
		{

		}

	}
}
void Room::setLevelDecrease(bool boo)
{
	LevelDecrease = boo;
}
void Room::resetRoom()
{
	InSceneObjects.clear();
	m_collider.clear();
	plat = nullptr;
	ladder = nullptr;
	pickUp = nullptr;
	respawner = nullptr;
	enemyHor = nullptr;
	mother = nullptr;
	firstLevel = false;
}

void Room::ChangeLevel(GameData * _GD, ID3D11Device * _pd3dDevice)
{
	resetRoom();
	map = level.LoadedLevels[levelCur].getMap();
	title = level.LoadedLevels[levelCur].getTitle();
	CreateRoom(_GD, _pd3dDevice);
	setPlayersSpawnPoint();
}

void Room::setPlayersSpawnPoint()
{
	if (levelIncrease)
	{
		player->SetPos(Vector2((Entrance->GetPos().x + 50), Entrance->GetPos().y));
		Playerspawn = Vector2((Entrance->GetPos().x + 50), Entrance->GetPos().y);
	}
	else if (LevelDecrease)
	{
		player->SetPos(Vector2((Exit->GetPos().x - 50), Exit->GetPos().y));
		Playerspawn = Vector2((Entrance->GetPos().x + 50), Entrance->GetPos().y);
	}
}

void Room::addToLists(GameObject2D * Object)
{
	InSceneObjects.push_back(Object);
	m_collider.push_back(Object);
}

void Room::addToPrevLevelList()
{
	/*if (preLevels[levelCur].size() != InSceneObjects.size())
	{*/
		//preLevels[levelCur] = InSceneObjects;
	//}
}

void Room::setLevelIncrease(bool boo)
{
	levelIncrease = boo;
}
