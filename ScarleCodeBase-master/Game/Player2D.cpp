#include "Player2D.h"
#include <dinput.h>
#include "GameData.h"


Player2D::Player2D(string _fileName, ID3D11Device* _GD) : ImageGO2D(_fileName, _GD)
{
	
	SetDrag(0.4);
	SetPhysicsOn(true);

}

Player2D::~Player2D()
{

}

void Player2D::Tick(GameData* _GD)
{
	//Add controls
	m_pos.y = 400;
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
	
	//forwardMove = Vector2(forwardMove);
	if (_GD->m_keyboardState[DIK_D] & 0x80)
	{
		m_acc += forwardMove;
	}
	if (_GD->m_keyboardState[DIK_A] & 0x80)
	{
		m_acc -= forwardMove;
	}

	if (m_physicsOn)
	{
		Vector2 newVel = m_vel + _GD->m_dt * (m_acc - m_drag*m_vel);
		Vector2 newPos = m_pos + _GD->m_dt * m_vel;

		m_vel = newVel;
		m_pos = newPos;
	}

	m_acc = Vector2::Zero;
	//m_pos = Vector2(posX, posY);


	//ImageGO2D::Tick(_GD);
}

void Player2D::Draw(DrawData2D* _DD)
{
	ImageGO2D::Draw(_DD);
}