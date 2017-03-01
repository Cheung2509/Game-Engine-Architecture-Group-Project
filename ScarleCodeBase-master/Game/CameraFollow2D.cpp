#include "CameraFollow2D.h"
#include "gamedata.h"
#include "DrawData2D.h"
#include "helper.h"

CameraFollow2D::CameraFollow2D(GameObject2D* _object, Vector2 _target, float _zoom) : Camera2D(_target, _zoom)
{
	m_targetObject = _object;
}

CameraFollow2D::~CameraFollow2D()
{

}

void CameraFollow2D::Tick(GameData* _GD)
{
	Matrix rotation = Matrix::CreateFromYawPitchRoll(0, 0, m_targetObject->GetRot());

	m_target = m_targetObject->GetPos();

	m_pos = m_target;

	Camera2D::Tick(_GD);
}