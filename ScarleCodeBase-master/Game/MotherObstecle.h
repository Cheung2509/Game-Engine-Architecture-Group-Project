#include "GameObject2D.h"

class Sprite;

class MotherObstacle : public GameObject2D
{
public:
	MotherObstacle(Sprite*, Vector2 Pos);
	~MotherObstacle();
	bool getBlocking() { return blocking; }
	void setBlocking(bool boo) { blocking = boo; }

	Sprite* getSprite() { return sprite; };

	virtual void Draw(DrawData2D* _DD);
private:
	Sprite* sprite;
	bool blocking;
};
