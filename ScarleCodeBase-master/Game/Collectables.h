#include "ImageGO2D.h"


class Collectables: public ImageGO2D
{
public:
	Collectables(string _fileName, ID3D11Device* _GD);
	~Collectables();
	bool GetPickedUp();
	void SetPickeduP();

private:
	bool PickedUp;
};
