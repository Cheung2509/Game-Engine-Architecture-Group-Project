#include "Player2D.h"
#include <dinput.h>
#include "GameData.h"

Player2D::Player2D(string _fileName, ID3D11Device* _GD) : ImageGO2D(_fileName, _GD)
{
	
}

Player2D::~Player2D()
{

}

void Player2D::Tick(GameData* _GD)
{
	//Add controls


	ImageGO2D::Tick(_GD);
}

void Player2D::Draw(DrawData2D* _DD)
{
	ImageGO2D::Draw(_DD);
}