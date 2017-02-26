#pragma once
#include "ImageGO2D.h"
class PlatfromTile :public ImageGO2D
{
public:
	PlatfromTile(string _fileName, ID3D11Device* _GD, Vector2 _pos);
	~PlatfromTile();


};

