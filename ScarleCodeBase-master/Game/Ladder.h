#pragma once
#include "GameObject2D.h"
#include <vector>
#include <memory>


class LadderTile;
class Ladder: public GameObject2D
{
public:
	Ladder(string _fileName, ID3D11Device* _GD, int _noOfTiles, float _initPosX, float _initPosY);
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

