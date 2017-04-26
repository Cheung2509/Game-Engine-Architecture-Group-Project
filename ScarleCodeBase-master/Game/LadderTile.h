#pragma once
#include "GameObject2D.h"

class Tile;

class LadderTile :public GameObject2D
{
public:
	LadderTile(Tile*, Vector2);
	~LadderTile();

	virtual void Draw(DrawData2D* _DD);

private:
	Tile* sprite;
};

