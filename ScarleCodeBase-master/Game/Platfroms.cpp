#include "Platfroms.h"

#include "Sprite.h"

Platforms::Platforms(Sprite* _sprite, int _noOfTiles, float _initPosX, float _initPosY)
{
	posX = _initPosX;
	posY = _initPosY;

	for (int i = 0; i < _noOfTiles; i++)
	{
		posX = _initPosX + incrementY;
		posY = _initPosY ;
		position = Vector2(posX, posY);
		_platfromTile.push_back(new Tile(_sprite, position));
		incrementY += 30;
	}

	float yPosition = _platfromTile[2]->GetPos().y;
}

void Platforms::Tick(GameData* _GD)
{
	for (vector<Tile*>::iterator it = _platfromTile.begin(); it != _platfromTile.end(); it++)
	{
		(*it)->Tick(_GD);
	}
}

void Platforms::Draw(DrawData2D* _DD)
{
	for (vector<Tile*>::iterator it = _platfromTile.begin(); it != _platfromTile.end(); it++)
	{
		(*it)->Draw(_DD);
	}
}

bool Platforms::checkCollisions(GameObject2D* _target)
{
	for (vector<Tile*>::iterator it = _platfromTile.begin(); it != _platfromTile.end(); ++it)
	{
		if ((*it)->checkCollisions(_target))
		{
			return true;
		}
	}

	return false;
}

		