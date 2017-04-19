#pragma once
#include "GameObject2D.h"

class Sprite;

class LadderTile :public GameObject2D
{
public:
	LadderTile(Sprite*, Vector2);
	~LadderTile();

	virtual void Draw(DrawData2D* _DD);

private:
	Sprite* sprite;
};

