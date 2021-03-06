#pragma once
#include "GameObject2D.h"
#include <vector>
#include <memory>
#include "Tile.h"

class Tile;
class Sprite;
class Platforms : public GameObject2D
{
public:
	Platforms(Sprite* _sprite, int _noOfTiles, float _initPosX, float _initPosY);
	virtual ~Platforms()=default;

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	//void PlatformForce(GameObject2D* gameObject);
	std::vector<Tile*> _platfromTile;
	int incrementY = 0;

	virtual bool checkCollisions(GameObject2D* _target) override;

	float posX;
	float posY;
	Vector2 position = Vector2(0.0f, 0.0f);

private:
	/*float EqualAndOpposite;
	Vector2 PlatfromUpMove;*/
};
