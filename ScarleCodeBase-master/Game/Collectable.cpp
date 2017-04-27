#include "Collectables.h"

Collectables::Collectables(string _fileName, ID3D11Device* _GD): ImageGO2D(_fileName, _GD)
{
	PickedUp = false;
	setType(COLLECTIBLE);
	SetScale(1.0f);
}
Collectables::~Collectables()
{

}



bool Collectables::GetPickedUp()
{
	return PickedUp;
}
void Collectables::SetPickeduP()
{
	PickedUp = true;
}

bool Collectables::GetRespawnUp()
{
	return m_RespawnUp;
}
		