#include "ImageGO2D.h"


class Platfroms : public ImageGO2D
{
public:
	Platfroms(string _fileName, ID3D11Device* _GD);
	~Platfroms()=default;
	void PlatformForce(GameObject2D* gameObject);

private:
	float EqualAndOpposite;
	Vector2 PlatfromUpMove;
};
