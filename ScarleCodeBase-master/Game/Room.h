#pragma once
#include <memory>
#include <vector>
#include <d3d11_1.h>
#include <list>
#include <string>

#include "GameObject2D.h"

class Levels;
class PlatfromTile;
class Tile;
//class RopeTile;
class Collectables;
class Enemy;
class MotherObstacle;
class Player2D;

class CameraFollow2D;
struct GameData;

class Room
{
public:
	friend class Levels;
	~Room() = default;

	std::string getRoomName() { return title; }
	std::vector<std::string> getRoomMap() { return map; }
	list<GameObject2D *> getColldingObjects(); 

	Player2D* getPlayer() { return player; }
	CameraFollow2D* getPlayerCamera() { return m_playerCam; }
	Collectables* getCollectable() { return pickUp; }
	Collectables* getRespawner() { return respawner; }
	Collectables* setRespawner(Collectables* _respawn) { _respawn = respawner; }
	MotherObstacle* getMother() { return mother; }
	/*Vector2 setRespawner(Vector2 _respawn) { respawner = _respawn; }*/

	void CreateRoom(GameData* _GD, ID3D11Device* _pd3dDevice);
	int getCurrentLevel() { return levelCur; }
	Vector2 getPlayerSpawn() { return Playerspawn; }
	void setCurrentLevel(int i);
	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);
	void setCollectableAlive();
	void addToLists(GameObject2D* Object);
	void addToPickUpList(Collectables* pickedColl);

	bool getLevelIncrease() { return levelIncrease; }
	void setLevelIncrease(bool boo);

	bool getLevelDecrease() { return LevelDecrease; }
	void setLevelDecrease(bool boo);

	void resetRoom();
	void ChangeLevel(GameData* _GD, ID3D11Device* _pd3dDevice);

	void setPlayersSpawnPoint();


private:
	Room(Levels&);
	Levels& level;

	int levelCur;
	bool levelIncrease;
	bool LevelDecrease;
	bool firstRespawn;

	std::string title;
	std::vector<std::string> map;


	Vector2 enemyStartPos;

	Vector2 incrementer;
	//possibly need to add a bool to stop two players being created 

	Enemy* enemyHor;
	MotherObstacle* mother;
	Tile* ladder;
	Tile* conveyorLeft;
	Tile* conveyorRight;
	Tile* ice;
	//RopeTile* Rope;
	Tile* plat;
	Tile* invisPlat;
	Tile* thinPlat;
	Collectables* pickUp;
	Collectables* collectables;
	Collectables* respawner;
	Collectables* Exit;
	Collectables* Entrance;


	Player2D* player;
	CameraFollow2D* m_playerCam;

	//vector<vector<Vector2>> PickedUpCollectables;
	list<GameObject2D *> InSceneObjects;//list to hold all objects created
	list<GameObject2D*> m_collider;
	vector<vector<Collectables*>> PickedUpCollectables;// a list of picked up collectables for each level 
	Vector2 Playerspawn;
};




