#include "MotherObstecle.h"

MotherObstecle::MotherObstecle(string _fileName, ID3D11Device* _GD, Vector2 Pos): ImageGO2D(_fileName, _GD)
{
	SetScale(0.05f);
	SetPos(Pos);
	setType(MOTHER);
}



