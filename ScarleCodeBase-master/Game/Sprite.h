#ifndef _Sprite_H_
#define _Sprite_H_

#include "GameObject2D.h"
#include "ImageGO2D.h"

class Sprite : public ImageGO2D
{
public:
	Sprite(string _fileName, ID3D11Device* _GD);
	~Sprite();

	int getSpriteWidth() { return m_spriteWidth; }
	int getSpriteHeight() { return m_spriteHeight; };
private:
	int m_spriteHeight;
	int m_spriteWidth;
};
#endif