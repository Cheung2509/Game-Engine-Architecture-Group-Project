#ifndef _SPRING_H_
#define _SPRING_H_

#include "GameObject2D.h"

class RopePiece;

class Spring : public GameObject2D
{
public:
	Spring(float, float, float, RopePiece*, RopePiece*);
	Spring(RopePiece*, RopePiece*);
	~Spring();

	virtual void Tick(GameData* _GD);
private:
	float m_springConstant;
	float m_springLength;
	float m_frictionConstant;

	RopePiece* m_rope1;
	RopePiece* m_rope2;
};
#endif // !_SPRING_H_
