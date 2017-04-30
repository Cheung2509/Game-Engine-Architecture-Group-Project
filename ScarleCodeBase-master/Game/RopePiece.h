#ifndef _ROPE_PIECE_H_
#define _ROPE_PIECE_H_

#include "GameObject2D.h"

class Sprite;

class RopePiece : public GameObject2D
{
public:
	RopePiece(Sprite*);
	~RopePiece();

	virtual void Tick(GameData* _GD);

	Sprite* getSprite() { return sprite; }
private:
	Sprite* sprite;
};
#endif // !_ROPE_PIECE_H_
