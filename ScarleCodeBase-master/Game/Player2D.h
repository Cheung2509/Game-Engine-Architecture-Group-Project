#pragma once
#ifndef _PLAYER2D_H_
#define _PLAYER2D_H_

#include "ImageGO2D.h"

class Player2D : public ImageGO2D
{
public:
	Player2D(string _fileName, ID3D11Device* _GD);
	~Player2D();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);
};

#endif