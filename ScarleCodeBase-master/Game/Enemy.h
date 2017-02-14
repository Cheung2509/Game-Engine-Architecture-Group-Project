#include "ImageGO2D.h"

//=================================================================
//Class for 2D Enemy
//Enemy can move horizontal or vertical not both 
//Enemy kills player when colliding
//=================================================================

class Enemy :public ImageGO2D
{
public:
	Enemy(string _fileName, ID3D11Device* _GD);
	~Enemy();

	virtual void Tick(GameData* _GD);
protected:



};