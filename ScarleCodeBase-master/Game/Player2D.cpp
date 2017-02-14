#include "Player2D.h"
#include <dinput.h>
#include "GameData.h"



Player2D::Player2D(string _fileName, ID3D11Device* _GD) : ImageGO2D(_fileName, _GD)
{
	SetDrag(0.4);
	SetPhysicsOn(true);
	m_PS = PS_MOVE;
}

Player2D::~Player2D()
{

}

void Player2D::Tick(GameData* _GD)
{
	/*
	if (_GD->m_keyboardState[DIK_A] & 0x80)
	{
		m_pos.x -= 0.1;
	}
	if (_GD->m_keyboardState[DIK_D] & 0x80)
	{
		m_pos.x += 0.1;
	}*/

	Vector2 forwardMove = 200.0f * Vector2(1.0f, 0.0f);
	Vector2 upMove = 500 * Vector2(0.0f, 1.0f);

	if (m_PS != PS_DEAD)
	{
		if (_GD->m_keyboardState[DIK_D] & 0x80)
		{
			m_acc += forwardMove;
		}
		if (_GD->m_keyboardState[DIK_A] & 0x80)
		{
			m_acc -= forwardMove;
		}

		//If space is pressed make player jump
		if (_GD->m_keyboardState[DIK_SPACE] & 0x80)
		{
			m_PS = PS_JUMP;
			m_acc -= upMove;
		}

		
	}


	if (m_physicsOn)
	{

		

		if (m_PS == PS_FALLING)
		{
			m_acc += upMove;
		}


		Vector2 newVel = m_vel + _GD->m_dt * (m_acc - m_drag*m_vel);
		Vector2 newPos = m_pos + _GD->m_dt * m_vel;
		
		m_vel = newVel;
		m_pos = newPos;

		if (m_vel.y >= -100 &&  m_pos.y < 400)
		{
             m_PS = PS_FALLING;
		}


		if (m_PS == PS_FALLING)
		{
			if (m_pos.y >= 400)
			{
				m_PS = PS_MOVE;
				m_vel = Vector2::Zero;
			}
		}

		

		//if acceleration is less than -20
	}

	m_acc = Vector2::Zero;
	//m_pos = Vector2(posX, posY);


	ImageGO2D::Tick(_GD);
}

void Player2D::Draw(DrawData2D* _DD)
{
	ImageGO2D::Draw(_DD);
}