#ifndef _PLAYER2D_H_
#define _PLAYER2D_H_

#include "ImageGO2D.h"

enum PlayerState
{
	PS_MOVE,
	PS_JUMP,
	PS_FALLING,
	PS_DEAD
};

class Player2D : public ImageGO2D
{
public:
	Player2D(string _fileName, ID3D11Device* _GD);
	~Player2D();
	int getCollectables();
	void addCollectable();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

private:
	PlayerState m_PS;
	int Collectables;
	bool isfalling = false;
};

#endif