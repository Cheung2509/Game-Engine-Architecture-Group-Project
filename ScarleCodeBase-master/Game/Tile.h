#ifndef _Tile_H_
#define _Tile_H_

#include "GameObject2D.h"
#include "ImageGO2D.h"

class Tile : public ImageGO2D
{
public:
	Tile(string _fileName, ID3D11Device* _GD);
	~Tile();

private:
};
#endif