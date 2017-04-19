#pragma once
#include "GameObject2D.h"

#include <vector>
#include <memory>


class LadderTile;
class Sprite;

class Ladder: public GameObject2D
{
public:
	Ladder(Sprite* _sprite, int _noOfTiles, float _initPosX, float _initPosY);
	virtual ~Ladder();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);
	std::vector<LadderTile*> ladderTiles;
	int incrementY = 0;

	float posX;
	float posY;
	Vector2 position = Vector2(0.0f, 0.0f);

private:
	
};

