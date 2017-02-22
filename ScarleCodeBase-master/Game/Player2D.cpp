#include "Player2D.h"
#include <dinput.h>
#include "GameData.h"



Player2D::Player2D(string _fileName, ID3D11Device* _GD) : ImageGO2D(_fileName, _GD)
{
	SetDrag(0.4);
	SetPhysicsOn(true);
	SetGravityOn(true);
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

	ImageGO2D::Tick(_GD);

	if (m_vel.y > 0)
	{
		m_PS = PlayerState::PS_FALLING;
	}
	else if (m_vel == Vector2::Zero)
	{
		m_PS = PlayerState::PS_IDLE;
	}
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
		if (m_PS != PS_FALLING && m_jumpTime < 0.5f)
		{
			//If space is pressed make player jump
			if (_GD->m_keyboardState[DIK_SPACE] & 0x80)
			{
				m_PS = PlayerState::PS_JUMP;

				m_acc -= upMove;
				
				if (_GD->m_prevKeyboardState == _GD->m_keyboardState)
				{
					m_jumpTime += _GD->m_dt;
				}
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