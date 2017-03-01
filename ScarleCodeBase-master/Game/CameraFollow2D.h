#ifndef _CAMERA_FOLLOW_2D_H_
#define _CAMERA_FOLLOW_2D_H_

#include "Camera2D.h"


class CameraFollow2D :public Camera2D
{
public:
	CameraFollow2D(GameObject2D* _object, Vector2 _target = Vector2::Zero, float _zoom = 1.0f);
	~CameraFollow2D();

	virtual void Tick(GameData* _GD) override;

protected:
	GameObject2D* m_targetObject;
};

#endif // !
