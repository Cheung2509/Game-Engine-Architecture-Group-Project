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
	player = nullptr;
	pickUp = nullptr;
	respawner = nullptr;
	enemyHor = nullptr;
	mother = nullptr;
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
	Sprite* _enemyHor = new Sprite("EnemyHor", _pd3dDevice);
	Sprite* _motherObstacle = new Sprite("motherFigure", _pd3dDevice);

	for (auto&& mapRow:map)
	{
		for(int i=0;i<mapRow.size();i++) 
		{
			if (TilePos.x >= _GD->viewportWidth)
			{
			TilePos.x = 0;
			TilePos.y += 50;//needs to be change to size of tile
			}
			switch (mapRow.at(i))
			{
			case '_':
				//create a platfrom;
				//TilePos.x = 0.0f + incrementY;
				plat = new Tile(_platform, TilePos);
				//plat->SetScale(1.0f);
				plat->setType(PLATFORM);
				InSceneObjects.push_back(plat);
				m_collider.push_back(plat);
				break;
			case'I':
				//invisible wall
				invisPlat = new Tile(_platform, TilePos);
				//invisPlat->//set rotation or set width plus height when functionailty is in there 
				invisPlat->SetAlive(false);
				InSceneObjects.push_back(invisPlat);
				m_collider.push_back(invisPlat);
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
				player = new Player2D("Walk", _pd3dDevice);
				player->SetScale(1.0f);
				player->SetPos(TilePos);
				player->setType(PLAYER);
				InSceneObjects.push_back(player);
				m_collider.push_back(player);

				m_playerCam = new CameraFollow2D(player);
				InSceneObjects.push_back(m_playerCam);
				//possibly create another platform here

				break;

			case'$':
				//create collecatable
				pickUp = new Collectables(_collectable);
				pickUp->SetPos(TilePos);
				InSceneObjects.push_back(pickUp);
				m_collider.push_back(pickUp);
				break;

			case '@':
				//create Respawner
				respawner = new Collectables(_respawn);
				respawner->SetScale(0.5f);
				respawner->SetPos(TilePos);

				InSceneObjects.push_back(respawner);
				respawner->setType(RESPAWN);
				m_collider.push_back(respawner);
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
				//if player does not have all the collectables 
				
					//create motherObstecle
					mother = new MotherObstacle(_motherObstacle, TilePos);
					InSceneObjects.push_back(mother);
					m_collider.push_back(mother);
				

			default:
				break;
			}
			TilePos.x += 30;//Tilesize
		}
	}
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
