#include "Platfroms.h"

Platforms::Platforms(string _fileName, ID3D11Device* _GD, int _noOfTiles, float _initPosX, float _initPosY)
{
	posX = _initPosX;
	posY = _initPosY;

	for (int i = 0; i < _noOfTiles; i++)
	{
		posX = _initPosX + incrementY;
		posY = _initPosY ;
		position = Vector2(posX, posY);
		_platfromTile.push_back(new PlatfromTile(_fileName, _GD, position));
		incrementY += 30;
	}

	float yPosition = _platfromTile[2]->GetPosY();

	/*EqualAndOpposite = 1000.0f;
	PlatfromUpMove = EqualAndOpposite * Vector2(0.0f, 10.0f);*/
}


//void Platforms::PlatformForce(GameObject2D* gameObject)
//{
//	gameObject->addForce(PlatfromUpMove);
//}


void Platforms::Tick(GameData* _GD)
{
	for (vector<PlatfromTile*>::iterator it = _platfromTile.begin(); it != _platfromTile.end(); it++)
	{
		(*it)->Tick(_GD);
	}
}

void Platforms::Draw(DrawData2D* _DD)
{
	for (vector<PlatfromTile*>::iterator it = _platfromTile.begin(); it != _platfromTile.end(); it++)
	{
		(*it)->Draw(_DD);
	}
}

bool Platforms::checkCollisions(GameObject2D* _target)
{
	for (vector<PlatfromTile*>::iterator it = _platfromTile.begin(); it != _platfromTile.end(); ++it)
	{
		if ((*it)->checkCollisions(_target))
		{
			return true;
		}
	}

	return false;
}

		