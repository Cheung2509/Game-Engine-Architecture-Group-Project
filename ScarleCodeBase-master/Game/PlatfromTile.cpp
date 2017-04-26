#include "PlatfromTile.h"

#include "Tile.h"

PlatfromTile::PlatfromTile(Tile* _sprite, Vector2 _pos)
{
	SetPos(_pos);
	SetScale(0.5f);
	
	SetIsGrounded(true);
	setType(ObjectType::PLATFORM);
	SetAlive(true);

	sprite = _sprite;
	sprite->SetScale(this->m_scale);
}


PlatfromTile::~PlatfromTile()
{
}

void PlatfromTile::Draw(DrawData2D * _DD)
{
	sprite->SetPos(m_pos);
	sprite->Draw(_DD);
}
