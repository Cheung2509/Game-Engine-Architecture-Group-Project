#include "GameObject2D.h"
#include "gamedata.h"
#include "DrawData2D.h"
#include "helper.h"

using namespace DirectX;

GameObject2D::GameObject2D()
{

	m_colour = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = Vector2::Zero;
	m_rotation = 0.0f;
	m_scale = Vector2::One;
	m_alive = true;

}

void GameObject2D::Tick(GameData* _GD)
{
	if (m_physicsOn)
	{
		//Move object down if gravity is on
		if (m_gravityOn == true)
		{
			m_acc += Vector2(0, 50);
		}

		//Claculating new velocity and position
		Vector2 newVel = m_vel + _GD->m_dt * (m_acc - m_drag*m_vel);
		Vector2 newPos = m_pos + _GD->m_dt * m_vel;

		m_vel = newVel;
		m_pos = newPos;
	}

	m_acc = Vector2::Zero;
}

ObjectType GameObject2D::GetType()
{
	return m_objectype;
}

void GameObject2D::SetSpeedY(float speed)
{
	speedY = speed;
}

void GameObject2D::SetIsGrounded(bool isItGrounded)
{
	isGrounded = isItGrounded;
}

void GameObject2D::setHasJumped(bool hasItJumped)
{
	hasJumped = hasItJumped;
}

void GameObject2D::setOnLadder(bool isOnLadder)
{
	onLadder = isOnLadder;
}


