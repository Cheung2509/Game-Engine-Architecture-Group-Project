#include "MotherObstecle.h"
#include "Sprite.h"
MotherObstacle::MotherObstacle(Sprite* _sprite, Vector2 Pos)
{
	sprite = _sprite;
	SetPos(Pos);
	setType(MOTHER);
	m_scale = Vector2(0.05, 0.05);
	blocking = true;
}

MotherObstacle::~MotherObstacle()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void MotherObstacle::Draw(DrawData2D * _DD)
{
	sprite->SetPos(m_pos);
	sprite->SetScale(m_scale);
	sprite->SetRot(m_rotation);
	sprite->Draw(_DD);
}


