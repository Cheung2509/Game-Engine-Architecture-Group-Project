#include "Ladder.h"
#include "LadderTile.h"

#include "Sprite.h"



Ladder::Ladder(Sprite* _sprite, int _noOfTiles, float _initPosX, float _initPosY)
{
	
	 posX = _initPosX;
	 posY = _initPosY;
	
	
	for (int i = 0; i < _noOfTiles; i++)
	{
		posX = _initPosX;
		posY = _initPosY - incrementY;
		position = Vector2(posX, posY);
		ladderTiles.push_back(new LadderTile(_sprite, position));
		incrementY -= 60;
	}


	
	/*for (auto& iter = ladder.begin(); iter < ladder.end(); iter++)
	{
		posX = _initPosX;
		posY = _initPosY - incrementY;
		position = Vector2(posX, posY);
		iter->get()->SetPos(position);
		incrementY -= 20;
	}*/
	//SetPos(Vector2(1, 1));
	//SetPos(_pos);
	
}


Ladder::~Ladder()
{
}

void Ladder::Tick(GameData* _GD)
{
	for (vector<LadderTile*>::iterator it = ladderTiles.begin(); it != ladderTiles.end(); it++)
	{
		(*it)->Tick(_GD);
	}
}

void Ladder::Draw(DrawData2D* _DD)
{
	for (vector<LadderTile*>::iterator it = ladderTiles.begin(); it != ladderTiles.end(); it++)
	{
		(*it)->Draw(_DD);
	}
}