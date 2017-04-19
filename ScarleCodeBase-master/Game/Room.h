#pragma once
#include <memory>
#include <vector>
#include <d3d11_1.h>
#include <list>
#include <string>

#include "GameObject2D.h"

class Levels;
class PlatfromTile;
class LadderTile;
class Player2D;
struct GameData;

class Room
{
public:
	friend class Levels;
	~Room() = default;

	std::string getRoomName() { return Title; }
	std::string getRoomMap() { return Map; }
	list<GameObject2D *> getObjectsInScene() { return InSceneObjects; }
	Player2D* getPlayer() { return player; }

	void CreateRoom(GameData* _GD, ID3D11Device* _pd3dDevice);
	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);


private:
	Room(Levels&);
	Levels& level;
	std::string Title;
	std::string Map;

	float incrementY;

	PlatfromTile*  plat;
	LadderTile* Ladder;
	Player2D* player;


	list<GameObject2D *> InSceneObjects;//list to hold all objects created
};



