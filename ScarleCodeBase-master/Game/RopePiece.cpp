#include "RopePiece.h"

#include "Sprite.h"

RopePiece::RopePiece(Sprite* _sprite)
{
	sprite = _sprite;
	m_gravityOn = true;
	m_physicsOn = true;
}

RopePiece::~RopePiece()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void RopePiece::Tick(GameData * _GD)
{
	GameObject2D::Tick(_GD);
}
