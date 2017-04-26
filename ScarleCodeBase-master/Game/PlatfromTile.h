#pragma once
#include "GameObject2D.h"

class Tile;
class PlatfromTile :public GameObject2D
{
public:
	PlatfromTile(Tile*, Vector2);
	~PlatfromTile();

	virtual void Draw(DrawData2D* _DD);

protected:
	Tile* sprite;
};

