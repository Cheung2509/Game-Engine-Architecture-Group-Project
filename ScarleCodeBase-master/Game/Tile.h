#pragma once
#include "GameObject2D.h"

class Sprite;

class Tile :public GameObject2D
{
public:
	Tile(Sprite*, Vector2);
	~Tile();

	virtual void Draw(DrawData2D* _DD);

	Sprite* getSprite() { return sprite; };
private:
	Sprite* sprite;
};

