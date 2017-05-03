#ifndef _PLAYER2D_H_
#define _PLAYER2D_H_

#include "GameObject2D.h"
#include "Sprite.h"
#include "Audio.h"
enum PlayerState
{
	PlayerState_IDLE,
	PlayerState_MOVE,
	PlayerState_JUMP,
	PlayerState_FALLING,
	PlayerState_DEAD,
	PlayerState_CLIMBING
};

class Player2D : public GameObject2D
{
public:
	Player2D(string _fileName, ID3D11Device* _GD);
	~Player2D();

	int getCollectables();
	void setCollectables(int _Collect) { Collectables = _Collect; }
	void addCollectable();

	int getLives();
	void TakeLives();
	void SetSpeedY(float speed);
	void SetIsGrounded(bool isItGrounded);
	void SetPlayerState(PlayerState state);

	void setLives(int _lives) { lives = _lives; }
	PlayerState GetPlayerState();
	bool getIsGrounded() { return isGrounded; }
	Sprite* getSprite() { return sprite; }

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	void MovementManagement(GameData* _GD);

private:
	PlayerState m_PS;

	int Collectables;
	int lives = 3;
	Vector2 forwardMove;
	Vector2 upMove;

	Sprite* sprite;
	std::unique_ptr<AudioEngine> m_audioEngine;
	std::unique_ptr<SoundEffect> m_JumpSound;
};

#endif