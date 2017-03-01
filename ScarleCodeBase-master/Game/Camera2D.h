#ifndef  _CAMERA_2D_H_
#define _CAMERA_2D_H_

//=================================================================
//Base 2D Camera Class
//=================================================================

#include "GameObject2D.h"

class Camera2D :public GameObject2D
{
public:
	Camera2D(Vector2 _target = Vector2::Zero, float _zoom = 1.0f);
	virtual ~Camera2D();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	float getZoom() { return m_zoom; }
	Matrix getTransform() { return m_transform; }

	void setZoom(float _zoom) { m_zoom = _zoom; if (m_zoom < 0.1f) { m_zoom = 0.1f; } }


	Matrix m_transform;
protected:
	float m_zoom;
	Vector2 m_target;
};

#endif // ! _CAMERA_2D_H_
