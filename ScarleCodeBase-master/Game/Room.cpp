#include "Room.h"
#include "Levels.h"
#include "gamedata.h"

#include "PlatfromTile.h"
#include "LadderTile.h"
#include "Player2D.h"

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
}


list<GameObject2D*> Room::getColldingObjects()
{
	 return m_collider; 
}

void Room::CreateRoom(GameData* _GD, ID3D11Device* _pd3dDevice)
{
	Vector2 TilePos(0, 0);  //x and y coordiantes of Tiles to be placed

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
				plat = new PlatfromTile("Platform", _pd3dDevice, TilePos);
				//plat->SetScale(1.0f);
				plat->setType(PLATFORM);
				InSceneObjects.push_back(plat);
				m_collider.push_back(plat);
				break;
			case'H':
				//create ladderTile
				Ladder = new LadderTile("ladder", _pd3dDevice, TilePos);
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
		Object->Draw(_DD);
	}
}
