#pragma once
#include "GameObject2D.h"
#include <vector>
#include <memory>


class PlatfromTile;
class Platfroms : public GameObject2D
{
public:
	Platfroms(string _fileName, ID3D11Device* _GD, int _noOfTiles, float _initPosX, float _initPosY);
	virtual ~Platfroms()=default;

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	void PlatformForce(GameObject2D* gameObject);
	std::vector<PlatfromTile*> _platfromTile;
	int incrementY = 0;

	float posX;
	float posY;
	Vector2 position = Vector2(0.0f, 0.0f);

private:
	float EqualAndOpposite;
	Vector2 PlatfromUpMove;
};
