#include"Enemy.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
Enemy::Enemy(string _fileName, ID3D11Device* _GD) :ImageGO2D(_fileName,_GD)
{

}
Enemy::~Enemy()
{

}



void Enemy::Tick(GameData* _GD)
{
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
