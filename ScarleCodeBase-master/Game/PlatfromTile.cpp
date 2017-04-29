#include "PlatfromTile.h"

#include "Sprite.h"

PlatfromTile::PlatfromTile(Sprite* _sprite, Vector2 _pos)
{
	SetPos(_pos);
	SetScale(0.5f);
	
	setType(ObjectType::PLATFORM);

	sprite = _sprite;
}


PlatfromTile::~PlatfromTile()
{
}

void PlatfromTile::Draw(DrawData2D * _DD)
{
	sprite->SetPos(m_pos);
	sprite->SetScale(m_scale);
	sprite->SetRot(m_rotation);
	sprite->Draw(_DD);
}
