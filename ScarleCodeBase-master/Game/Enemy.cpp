#include"Enemy.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include "Sprite.h"

Enemy::Enemy(Sprite* _sprite, Vector2 startpos, Vector2 endpos)
{
	setType(ENEMY);
	movingRight = true;
	StartPostion = startpos;
	EndPostion = endpos;
	m_pos = StartPostion;
	if (StartPostion.y == EndPostion.y)
	{
		movingVerticaly = false;
	}
	else
	{
		movingVerticaly = true;
	}
	if (StartPostion.x == EndPostion.x)
	{
		movinghorizantel = false;
	}
	else
	{
		movinghorizantel = true;
	}

	sprite = _sprite;
}

Enemy::~Enemy()
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}



void Enemy::Tick(GameData* _GD)
{
	//chcek if enemy is at end postion for left or right and move it to the other end positon direction 	
	checkHorizontal();
	checkVertical();
	if (movinghorizantel)
	{
		if (movingRight)//check enemy postion if at left end postion move right 
		{
			//move right
			m_pos += Vector2(0.1, 0);
		}
		else
		{
			//move left 
			m_pos += Vector2(-0.1, 0);
		}
	}
	if (movingVerticaly)
	{
		if (movingUp)
		{
			m_pos += Vector2(0, 0.1);
		}
		else
		{
			m_pos += Vector2(0, -0.1);
		}
	}


}
void Enemy::Draw(DrawData2D * _DD)
{
	sprite->SetPos(m_pos);
	sprite->SetScale(m_scale);
	sprite->SetRot(m_rotation);
	sprite->Draw(_DD);
}

bool Enemy::checkHorizontal()
{

	if (m_pos.x <= StartPostion.x)
	{
		movingRight = true;
	}
	if (m_pos.x >= EndPostion.x)//check enemy postion if at right end postion move left
	{
		movingRight = false;
	}
	
	return movingRight;

}
bool Enemy::checkVertical()
{
	if (m_pos.y <= StartPostion.y)
	{
		movingUp = true;
	}
	if (m_pos.y >= EndPostion.y)
	{
		movingUp = false;
	}
	return movingUp;
	//not finished yet need to fix

	//chcek if enemy is at end postion for left or right and move it to the other end positon direction
	m_pos += Vector2(-1, 0);//if not at left or right end postion move right 

	if (m_pos == 200.0f * Vector2(3.5, 2))//check enemy postion if at right end postion move left
	{
		//move left 
		m_pos += Vector2(-1, 0);
	}
	if (m_pos == 200.0f * Vector2(0.5, 2))//check enemy postion if at left end postion move right 
	{
		m_pos += Vector2(1, 0);
	}
}
