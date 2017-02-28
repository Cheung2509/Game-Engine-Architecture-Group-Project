#include "Player2D.h"

#include <dinput.h>
#include <iostream>

#include "GameData.h"




Player2D::Player2D(string _fileName, ID3D11Device* _GD, int _frameCount) : AnimatedSprite(_fileName, _GD, _frameCount)
{
	/*SetDrag(1);
	SetPhysicsOn(true);
	SetGravityOn(true);
	m_PS = PlayerState_MOVE;
	Collectables = 0;
	lives = 3;
	upMove = 500 * Vector2(0.0f, 1.0f);
	forwardMove = 200.0f * Vector2(1.0f, 0.0f);*/
	//m_fudge = Matrix::CreateRotationY(XM_PI);

	m_pos.y = 0.5f;
	speed = 0.0f;
	topSpeed = 6 *40 ;
	accel = 0.046875 * 40;
	decel = 0.5* 40;
	friction = 0.046875 * 40;
	isGrounded = true;
	airAccel = 0.09375 * 40;
	speedY = 0.0f;
	grav = 0.21875;
	jumpSpeed = -3.5*40;

	SetDrag(friction);
	
	SetPhysicsOn(true);

}

Player2D::~Player2D()
{

}

void Player2D::Tick(GameData* _GD)
{
	

	if (_GD->m_keyboardState[DIK_D] & 0x80)
	{

		//checks if player is pressing against their direction or forward
		if (speed < 0)
		{
			if (isGrounded)
			{
				m_PS = PlayerState::PlayerState_MOVE;
			}
			speed += decel;


		}
		else if (speed < topSpeed)
		{
			if (!isGrounded)
			{
				speed += airAccel;
			}
			else
			{
				speed += accel;
				m_PS = PlayerState::PlayerState_MOVE;
			}

		}

	}
	else if (_GD->m_keyboardState[DIK_A] & 0x80)
	{
		if (speed > 0)
		{
			if (isGrounded)
			{
				m_PS = PlayerState::PlayerState_MOVE;
			}
			speed -= decel;

		}
		else if (speed > -topSpeed)
		{
			if (!isGrounded)
			{
				speed -= airAccel;
			}
			else
			{
				speed -= accel;
				m_PS = PlayerState::PlayerState_MOVE;
			}
		}
	}
	else
	{
		if (isGrounded)
		{
			speed = 0;
		}
	}

	//jump functionality 
	if (_GD->m_keyboardState[DIK_W] & 0x80)
	{

		if (isGrounded)
		{
			speedY = jumpSpeed;
			isGrounded = false;
			printf("jumped\n");
			m_PS = PlayerState::PlayerState_JUMP;

		}
		else
		{
			speedY += grav;
			if (speedY >= 16 * 40)
			{
				speedY = 16 * 40;
			}
			//speedY = prevYSpeed;
		}
	}
	else
	{

		if (speedY > 4 * 40)
		{
			speedY = 4 * 40;
		}

		if (!isGrounded)
		{
			speedY += grav;
			if (speedY >= 16 * 40)
			{
				speedY = 16 * 40;
			}
		}

	}


	if (speedY > 0 && speedY < 4 * 40)
	{
		float airDrag = 0.96875;
		if (speed < 0.125 * 40)
		{
			speed = speed * airDrag;
		}
	}


	//create the transform based on speed
	forwardMove = speed * Vector2(1, 0);
	upMove = speedY * Vector2(0, 1);
	Matrix rotMove = Matrix::CreateRotationY(0);
	upMove = Vector2::Transform(upMove, rotMove);
	forwardMove = Vector2::Transform(forwardMove, rotMove);

	//make the player move based on speed calcs
	m_acc += forwardMove;
	m_acc += upMove;

	std::cout << speedY << "\n";

	if (m_physicsOn)
	{
		float newVelX = m_vel.x + _GD->m_dt * (m_acc.x - m_drag *m_vel.x);
		//float newVelY = m_vel.y + _GD->m_dt * (m_acc.y - m_drag*m_vel.y);
		float newVelY = m_acc.y;
		//could also do same for Z

		Vector2 newVel = Vector2(newVelX, newVelY);
		//m_vel + _GD->m_dt * (m_acc - m_drag*m_vel);

		Vector2 newPos = m_pos + (_GD->m_dt * m_vel);


		m_vel = newVel;
		m_pos = newPos;

		m_acc = Vector2::Zero;
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

				GameObject2D::addForce(Vector2(0, -200 * _GD->m_dt));

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

void Player2D::SetSpeedY(float speed)
{
	speedY = speed;
}

void Player2D::SetIsGrounded(bool isItGrounded)
{
	isGrounded = isItGrounded;
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