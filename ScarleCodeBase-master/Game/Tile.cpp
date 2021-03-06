#include "Tile.h"

#include "Sprite.h"

Tile::Tile(Sprite* sp, Vector2 _pos)
{
	SetPos(_pos);
	SetScale(0.5f);
	sprite = sp;
}


Tile::~Tile()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void Tile::Draw(DrawData2D * _DD)
{
	sprite->SetPos(m_pos);
	sprite->SetScale(m_scale);
	sprite->SetRot(m_rotation);
	sprite->SetColour(m_colour);
	sprite->Draw(_DD);
}

