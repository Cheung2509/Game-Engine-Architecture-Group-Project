#include "Room.h"
#include "Levels.h"
#include "gamedata.h"

#include "Tile.h"

#include "PlatfromTile.h"
#include "LadderTile.h"
#include "Player2D.h"
#include "Collectables.h"

#include "CameraFollow2D.h"

#include <sstream>
#include<Windows.h>

Room::Room(Levels& L) :
	level(L)
{
	Title = L.getTitle();
	Map =L.getMap();

	plat = nullptr;
	Ladder = nullptr;
	player = nullptr;
	PickUp = nullptr;
}


list<GameObject2D*> Room::getColldingObjects()
{
	 return m_collider; 
}

void Room::CreateRoom(GameData* _GD, ID3D11Device* _pd3dDevice)
{
	Vector2 TilePos(0, 0);  //x and y coordiantes of Tiles to be placed

	Tile* _platform = new Tile("Platform", _pd3dDevice);
	Tile* _ladder = new Tile("Ladder", _pd3dDevice);

	for (int i = 0; i < Map.size(); i++)
	{
		if (TilePos.x >= _GD->viewportWidth)
		{
			TilePos.x = 0;
			TilePos.y += 15;//needs to be change to size of tile
		}

			switch (Map.at(i))
			{
			case 'O':
				// do nothing 
				break;
			case '_':
				//create a platfrom;
				//TilePos.x = 0.0f + incrementY;
				plat = new PlatfromTile(_platform, TilePos);
				//plat->SetScale(1.0f);
				plat->setType(PLATFORM);
				InSceneObjects.push_back(plat);
				m_collider.push_back(plat);
				break;
			case'H':
				//create ladderTile
				Ladder = new LadderTile(_ladder, TilePos);
				InSceneObjects.push_back(Ladder);
				m_collider.push_back(plat);
				break;
			case'*':
				// create player 
				player = new Player2D("PlayerSpriteSheet", _pd3dDevice, 3);
				player->SetScale(1.0f);
				player->SetPos(TilePos);
				player->setType(PLAYER);
				InSceneObjects.push_back(player);
				m_collider.push_back(player);

				m_playerCam = new CameraFollow2D(player);
				InSceneObjects.push_back(m_playerCam);
				break;
			case'$':
				//create collecatable
				PickUp = new Collectables("Collectable", _pd3dDevice);
				PickUp->SetScale(1.0f);
				PickUp->SetPos(TilePos);
				PickUp->setType(COLLECTIBLE);

				InSceneObjects.push_back(PickUp);
				m_collider.push_back(PickUp);
				break;

			default:
				break;
			}
			TilePos.x += 30;//Tilesize
	}
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
