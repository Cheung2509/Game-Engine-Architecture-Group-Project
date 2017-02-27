#include "PlatfromTile.h"



PlatfromTile::PlatfromTile(string _fileName, ID3D11Device* _GD, Vector2 _pos) : ImageGO2D(_fileName, _GD)
{
	SetPos(_pos);
	SetScale(0.5f);
	setType(ObjectType::PLATFORM);
	SetAlive(true);
}


PlatfromTile::~PlatfromTile()
{
}
