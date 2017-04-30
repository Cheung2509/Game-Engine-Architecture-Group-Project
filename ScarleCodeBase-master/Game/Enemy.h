#include "GameObject2D.h"

//=================================================================
//Class for 2D Enemy
//Enemy can move horizontal or vertical not both 
//Enemy kills player when colliding
//=================================================================

class Sprite;

class Enemy :public GameObject2D
{
public:
	Enemy(Sprite* sprite , Vector2 startpos, Vector2 endpos);
	~Enemy();
	bool checkHorizontal();
	bool checkVertical();

	Sprite* getSprite() { return sprite; }

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);
protected:

	bool movingRight;
	bool movingUp;
	bool movingVerticaly;
	bool movinghorizantel;
	Vector2 StartPostion;
	Vector2 EndPostion;
	Sprite* sprite;
};