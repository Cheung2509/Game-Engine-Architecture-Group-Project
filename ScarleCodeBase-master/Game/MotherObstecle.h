#include "GameObject2D.h"

class Sprite;

class MotherObstacle : public GameObject2D
{
public:
	MotherObstacle(Sprite*, Vector2 Pos);
	~MotherObstacle();

	Sprite* getSprite() { return sprite; };

	virtual void Draw(DrawData2D* _DD);
private:
	Sprite* sprite;
};
