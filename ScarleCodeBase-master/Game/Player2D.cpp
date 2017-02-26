#include "Player2D.h"

#include <dinput.h>
#include <iostream>

#include "GameData.h"




Player2D::Player2D(string _fileName, ID3D11Device* _GD, int _frameCount) : AnimatedSprite(_fileName, _GD, _frameCount)
{
	SetDrag(0.4);
	SetPhysicsOn(true);
	SetGravityOn(true);
	m_PS = PlayerState_MOVE;
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

	if (m_vel.y > 0)
	{
		std::cout << "Falling \n";
		m_PS = PlayerState::PlayerState_FALLING;
	}
	else if (m_vel.x != 0)
	{
		m_PS = PlayerState::PlayerState_MOVE;
	}
	else if (m_vel == Vector2::Zero)
	{
		std::cout << "Idle \n";
		m_PS = PlayerState::PlayerState_IDLE;
	}

	//switch statement to determine which frame to render
	switch (m_PS)
	{
	case PlayerState_MOVE:
		if (_GD->m_GS != GS_PAUSE)
		{
			m_totalElapsed += _GD->m_dt;

			if (m_totalElapsed > m_timePerFrame)
			{
				++m_frame;
				m_frame = m_frame % m_frameCount; 
				m_totalElapsed -= m_timePerFrame;
			}
		}
		break;
	case PlayerState_IDLE:
		m_frame = 0;
		break;
	case PlayerState_JUMP:
		m_frame = 2;
		break;
	case PlayerState_FALLING:
		m_frame = 2;
		break;
	}

	AnimatedSprite::Tick(_GD);
}

void Player2D::MovementManagement(GameData* _GD)
{
	//if player is not dead
	if (m_PS != PlayerState_DEAD)
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
		if (m_PS != PlayerState_FALLING && m_jumpTime < 0.5f)
		{
			//If space is pressed make player jump
			if (_GD->m_keyboardState[DIK_SPACE] & 0x80)
			{
				m_PS = PlayerState::PlayerState_JUMP;

				GameObject2D::addForce(Vector2(0, -100 * _GD->m_dt));

				if (_GD->m_prevKeyboardState[DIK_SPACE])
				{
					m_jumpTime += _GD->m_dt;
				}
				std::cout << "Jumping \n";
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

void Player2D::resetJumpTime()
{
	m_jumpTime = 0;
}


void Player2D::Draw(DrawData2D* _DD)
{
	int frameWidth = m_frameWidth / m_frameCount;

	sourceRect->left = frameWidth * m_frame;
	sourceRect->right = sourceRect->left + frameWidth;
	sourceRect->top = 0;
	sourceRect->bottom = m_frameHeight;

	AnimatedSprite::Draw(_DD);
}