#include "Spring.h"

#include "RopePiece.h"

Spring::Spring(float _springConstant, float _springLength, float _frictionConstant, RopePiece* _rope1, RopePiece* _rope2)
{
	m_springConstant = _springConstant;
	m_springLength = _springLength;
	m_frictionConstant = _frictionConstant;

	m_rope1 = _rope1;
	m_rope2 = _rope2;
}

Spring::Spring(RopePiece* _rope1, RopePiece* _rope2)
{
	m_rope1 = _rope1;
	m_rope2 = _rope2;

	m_springConstant = 1.0f;
	m_springLength = 1.0f;
	m_frictionConstant = 1.0f;
}

Spring::~Spring()
{
}

void Spring::Tick(GameData * _GD)
{
	Vector2 _springVector = m_rope1->GetPos() - m_rope2->GetPos();

	float length = _springVector.Length();

	Vector2 force;

	if (length != 0)
	{
		force += -(_springVector / length) * (length - m_springLength) * m_springConstant;

		force += (m_rope1->GetVel() - m_rope2->GetVel()) * m_frictionConstant;
	}

	m_rope1->addForce(force);
	m_rope2->addForce(-force);
}
