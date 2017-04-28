#include "Background.h"

Background::Background(string _fileName, ID3D11Device* _GD): ImageGO2D(_fileName, _GD)
{
	SetScale(1.0f);
	SetPos(Vector2(100.0f,100.0f));
}

