#include "Player2D.h"

#include <dinput.h>
#include <iostream>

#include "GameData.h"
#include "DrawData2D.h"



Player2D::Player2D(string _fileName, ID3D11Device* _GD)
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
	grav = 0.21875*5;
	jumpSpeed = -6.5*50;

	SetDrag(friction);
	
	SetPhysicsOn(true);

	sprite = new Sprite(_fileName, _GD);
}

Player2D::~Player2D()
{

}

void Player2D::Tick(GameData* _GD)
{
	if (_GD->m_GS != GS_PLAY_DEBUG_CAM)
	{
		MovementManagement(_GD);
	}
}

void Player2D::MovementManagement(GameData* _GD)
{

	//THIS IS WHERE THE PHYSICS HAPPEN
	//BUT ONLY BASE PHYSICS. CHANGES TO THE PLAYER THROUGH INTERACTION WITH OBJECTS WILL BE IN THE GAME.CPP WITH COLLISION STUFF
	if (m_PS == PlayerState::PlayerState_CLIMBING)
	{
		isGrounded = true;
		speedY = 0.0f;

		if (_GD->m_keyboardState[DIK_S] & 0x80)
		{

			m_pos.y++;

		}

	}

	if (isGrounded == false)
	{
		m_PS = PlayerState::PlayerState_FALLING;
	}

	if (_GD->m_keyboardState[DIK_D] & 0x80)
	{
		//checks if player is pressing against their direction or forward
		if (speed < 0)
		{
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
			}
		}
	}
	else if (_GD->m_keyboardState[DIK_A] & 0x80)
	{
		if (speed > 0)
		{
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
			}
		}
	}
	else
	{
		if (isGrounded)
		{
			if (speed < 0.125*40 && speed > -0.125 *40)
			{
				speed = 0;
			}
			else
			{
				if (speed > 0)
				{
					speed -= friction;
				}
				else if (speed < 0)
				{
					speed += friction;
				}

			}

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
			hasJumped = true;
		}
		else
		{
			speedY += grav;

			if (speedY >= 16 * 40)
			{
				speedY = 16 * 40;
			}

		}
	}
	else
	{
		if (hasJumped)
		{
			if (speedY < -2 * 50)
			{
				speedY = -2 * 50;
			}
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
	if (speedY > 0 && speedY > -4 * 40)
	{
		float airDrag = 0.96875;
		if (speed > 0.125 * 40)
		{
			speed = speed * airDrag;
		}
	}
	SetDrag(friction);

	if (_GD->m_keyboardState[DIK_W] & 0x80)
	{
		if (onLadder)
		{
			m_pos.y = m_pos.y--;
		}
	}

	if (_GD->m_keyboardState[DIK_S] & 0x80)
	{
		if (onLadder)
		{
			m_pos.y = m_pos.y++;
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

	if (_GD->m_keyboardState[DIK_R] & 0x80)
	{
		printf("Debug");
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



void Player2D::SetPlayerState(PlayerState state)
{
	m_PS = state;
}
PlayerState Player2D::GetPlayerState()
{
	return m_PS;
}



void Player2D::Draw(DrawData2D* _DD)
{
	sprite->SetPos(m_pos);
	sprite->SetScale(m_scale);
	sprite->SetRot(m_rotation);
	sprite->Draw(_DD);
}