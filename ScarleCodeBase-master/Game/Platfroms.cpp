#include "Platfroms.h"

Platfroms::Platfroms(string _fileName, ID3D11Device* _GD): ImageGO2D(_fileName, _GD)
{
	EqualAndOpposite = 1000.0f;
	PlatfromUpMove = EqualAndOpposite * Vector2(0.0f, 1.0f);
}


void Platfroms::PlatformForce(GameObject2D* gameObject)
{
	//gameObject->addForce(PlatfromUpMove);
}
		