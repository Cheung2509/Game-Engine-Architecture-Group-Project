#include "LadderTile.h"

#include "Sprite.h"

LadderTile::LadderTile(Sprite* sp, Vector2 _pos)
{
	SetPos(_pos);
	SetScale(0.5f);

	setType(ObjectType::LADDER);

	sprite = sp;
}


LadderTile::~LadderTile()
{
	
}

void LadderTile::Draw(DrawData2D * _DD)
{
	sprite->SetPos(m_pos);
	sprite->SetScale(m_scale);
	sprite->SetRot(m_rotation);
	sprite->Draw(_DD);
}

