#include "Collectables.h"
#include "Sprite.h"

Collectables::Collectables(Sprite* _sprite)
{
	PickedUp = false;
	setType(COLLECTIBLE);
	SetScale(1.0f);

	sprite = _sprite;
}
Collectables::~Collectables()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}



bool Collectables::GetPickedUp()
{
	return PickedUp;
}
void Collectables::SetPickeduP()
{
	PickedUp = true;
}

bool Collectables::GetRespawnUp()
{
	return m_RespawnUp;
}

void Collectables::Draw(DrawData2D * _DD)
{
	sprite->SetPos(m_pos);
	sprite->SetScale(m_scale);
	sprite->SetRot(m_rotation);
	sprite->Draw(_DD);
}
		