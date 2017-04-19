#include "Room.h"
#include "Levels.h"
#include "gamedata.h"

#include "Sprite.h"

#include "PlatfromTile.h"
#include "LadderTile.h"
#include "Player2D.h"

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


void Room::CreateRoom(GameData* _GD, ID3D11Device* _pd3dDevice)
{
	Vector2 TilePos(0, 0);  //x and y coordiantes of Tiles to be placed

	Sprite* _platform = new Sprite("Platform", _pd3dDevice);
	Sprite* _ladder = new Sprite("Ladder", _pd3dDevice);

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
				//m_collider.push_back(plat);
				break;
			case'H':
				//create ladderTile
				Ladder = new LadderTile(_ladder, TilePos);
				InSceneObjects.push_back(Ladder);
				break;
			//case'*':
				// create player 
				/*player = new Player2D("PlayerSpriteSheet", _pd3dDevice, 3);
				player->SetScale(1.0f);
				player->SetPos(Vector2(200, 430));
				player->setType(PLAYER);
				InSceneObjects.push_back(player);*/

				/*m_playerCam = new CameraFollow2D(player);
				m_GameObject2Ds.push_back(m_playerCam);*/
			default:
				break;
			}
			TilePos.x += 30;//Tilesize
	}
	//return InSceneObjects;
}

void Room::Tick(GameData* _GD)
{
	/*for (auto& Object : InSceneObjects)
	{
		Object->Tick(_GD);
	}*/
}

void Room::Draw(DrawData2D* _DD)
{
	for (auto& Object : InSceneObjects)
	{
		Object->Draw(_DD);
	}
}
