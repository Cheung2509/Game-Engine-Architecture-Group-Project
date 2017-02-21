#include "Collectables.h"

Collectables::Collectables(string _fileName, ID3D11Device* _GD): ImageGO2D(_fileName, _GD)
{
	PickedUp = false;
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
		