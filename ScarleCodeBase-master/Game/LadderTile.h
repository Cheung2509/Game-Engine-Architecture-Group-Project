#pragma once
#include "ImageGO2D.h"
class LadderTile :public ImageGO2D
{
public:
	LadderTile(string _fileName, ID3D11Device* _GD, Vector2 _pos);
	~LadderTile();


};

