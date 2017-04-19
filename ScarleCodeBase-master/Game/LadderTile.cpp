#include "LadderTile.h"

#include "Sprite.h"

LadderTile::LadderTile(Sprite* sp, Vector2 _pos)
{
	SetPos(_pos);
	SetScale(0.5f);
	setType(ObjectType::LADDER);
	sprite = sp;
	sprite->SetScale(this->m_scale);
}


LadderTile::~LadderTile()
{
	
}

void LadderTile::Draw(DrawData2D * _DD)
{
	sprite->SetPos(m_pos);
	sprite->Draw(_DD);
}

