#include "ImageGO2D.h"


class Background: public ImageGO2D
{
public:
	Background(string _fileName, ID3D11Device* _GD);
	~Background()=default;
	
};
