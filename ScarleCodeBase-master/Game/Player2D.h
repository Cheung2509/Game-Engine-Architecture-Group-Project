#ifndef _PLAYER2D_H_
#define _PLAYER2D_H_

#include "AnimatedSprite.h"

enum PlayerState
{
	PlayerState_IDLE,
	PlayerState_MOVE,
	PlayerState_JUMP,
	PlayerState_FALLING,
	PlayerState_DEAD,
	PlayerState_CLIMBING
};

class Player2D : public AnimatedSprite
{
public:
	Player2D(string _fileName, ID3D11Device* _GD, int _frameCount);
	~Player2D();

	int getCollectables();
	void addCollectable();

	int getLives();
	void TakeLives();
	void SetSpeedY(float speed);
	void SetIsGrounded(bool isItGrounded);

	void resetJumpTime();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	void MovementManagement(GameData* _GD);

private:
	PlayerState m_PS;

	int Collectables;
	bool isfalling = false;
	float m_jumpTime;
	int lives;
	Vector2 forwardMove;
	Vector2 upMove;

	float speed;
	float topSpeed;
	float accel;
	float decel;
	float friction;
	bool isGrounded;
	float speedY;
	float airAccel;
	float grav;
	float jumpSpeed;
	
};

#endif