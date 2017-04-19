#pragma once
#include "GameObject2D.h"

class Sprite;
class PlatfromTile :public GameObject2D
{
public:
	PlatfromTile(Sprite*, Vector2);
	~PlatfromTile();

	virtual void Draw(DrawData2D* _DD);

protected:
	Sprite* sprite;
};

