#include "ImageGO2D.h"

//=================================================================
//Class for 2D Enemy
//Enemy can move horizontal or vertical not both 
//Enemy kills player when colliding
//=================================================================

class Enemy :public ImageGO2D
{
public:
	Enemy(string _fileName, ID3D11Device* _GD,Vector2 startpos,Vector2 endpos);
	~Enemy();
	bool checkHorizontal();
	bool checkVertical();

	virtual void Tick(GameData* _GD);
protected:
<<<<<<< HEAD



=======
	bool movingRight;
	bool movingUp;
	bool movingVerticaly;
	bool movinghorizantel;
	Vector2 StartPostion;
	Vector2 EndPostion;
>>>>>>> refs/remotes/origin/master
};