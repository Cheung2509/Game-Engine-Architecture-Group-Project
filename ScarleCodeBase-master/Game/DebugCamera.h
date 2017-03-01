#ifndef _DEBUG_CAMERA_H_
#define _DBUG_CAMERA_H_

#include "Camera2D.h"

class DebugCamera : public Camera2D
{
public:
	DebugCamera(Vector2 _target = Vector2::Zero, float _zoom = 1.0f);
	~DebugCamera();

	virtual void Tick(GameData* _GD);
protected:
};

#endif 
