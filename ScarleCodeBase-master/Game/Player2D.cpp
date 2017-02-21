#include "Player2D.h"
#include <dinput.h>
#include "GameData.h"



Player2D::Player2D(string _fileName, ID3D11Device* _GD) : ImageGO2D(_fileName, _GD)
{
	SetDrag(0.4);
	SetPhysicsOn(true);
	m_PS = PS_MOVE;
	Collectables = 0;
	lives = 3;
	upMove = 500 * Vector2(0.0f, 1.0f);
	forwardMove = 200.0f * Vector2(1.0f, 0.0f);
}

Player2D::~Player2D()
{

}

void Player2D::Tick(GameData* _GD)
{
	MovementManagement(_GD);

	if (m_physicsOn)
	{
		//if the player is falling
		if (m_PS == PS_FALLING)
		{
			//Move player downwards
			m_acc += upMove;
		}
		else if (m_PS == PS_JUMP)
		{
			m_jumpTime = m_jumpTime + _GD->m_dt;
		}

		//Claculating new velocity and position
		Vector2 newVel = m_vel + _GD->m_dt * (m_acc - m_drag*m_vel);
		Vector2 newPos = m_pos + _GD->m_dt * m_vel;
		
		m_vel = newVel;
		m_pos = newPos;

		//if velocity is low while and has been in the air for more than half a second
		if ((m_vel.y >= -100 && m_pos.y < 400) || m_jumpTime > 0.5f)
		{
			//set player state to fall
			m_PS = PS_FALLING;
		}


		////if player state is falling and the player height is over 400
		//if (m_PS == PS_FALLING && m_pos.y >= 400)
		//{
		//	//Set the player to move
		//	m_PS = PS_MOVE;

		//	//Set velocity to zero to stop it from moving any further down
		//	m_vel = Vector2::Zero;

		//	//reset jump time when the player is grounded
		//	m_jumpTime = 0;
		//}
	}

	m_acc = Vector2::Zero;

	ImageGO2D::Tick(_GD);
}

void Player2D::MovementManagement(GameData* _GD)
{
	//if player is not dead
	if (m_PS != PS_DEAD)
	{
		//player moves left or right
		if (_GD->m_keyboardState[DIK_D] & 0x80)
		{
			m_acc += forwardMove;
		}
		if (_GD->m_keyboardState[DIK_A] & 0x80)
		{
			m_acc -= forwardMove;
		}

		//if player is not falling and space is  not held over 0.5 seconds
		if (m_PS != PS_FALLING || m_jumpTime < 0.5f)
		{
			//If space is pressed make player jump
			if (_GD->m_keyboardState[DIK_SPACE] & 0x80)
			{
				m_PS = PS_JUMP;
				m_acc -= upMove;
			}
		}
	}
}

int Player2D::getCollectables()
{
	return Collectables;
}
void Player2D::addCollectable()
{
	Collectables++;
}
int Player2D::getLives()
{
	return lives;
}
void Player2D::TakeLives()
{
	lives--;
}

void Player2D::Draw(DrawData2D* _DD)
{
	ImageGO2D::Draw(_DD);
}