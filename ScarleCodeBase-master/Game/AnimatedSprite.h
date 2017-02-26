#ifndef _ANIMATED_SPRITE_2D_
#define _ANIMATED_SPRITE_2D_

#include "ImageGO2D.h"

class AnimatedSprite :public ImageGO2D
{
public:
	AnimatedSprite(string _fileName, ID3D11Device* _GD, int frameCount);
	virtual ~AnimatedSprite();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

protected:
	float m_timePerFrame;	//Time needed to go to the next frame
	float m_totalElapsed;	//Time since the last time the frame changed
	int m_frameCount;		//The amount of frames the animation has
	int m_frame;			//Which frame the animation is currently on
	int m_frameWidth;
	int m_frameHeight;

	RECT* sourceRect;
	
};
#endif
