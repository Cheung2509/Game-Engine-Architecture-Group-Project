#include "Camera2D.h"
#include "gamedata.h"
#include "DrawData2D.h"
#include "helper.h"

Camera2D::Camera2D(Vector2 _target, float _zoom)
{
	m_zoom = _zoom;
	m_target = _target;
}

Camera2D::~Camera2D()
{

}

void Camera2D::Tick(GameData* _GD)
{
	if (_GD->m_GS == GS_PLAY_DEBUG_CAM)
	{
		if (_GD->m_keyboardState[DIK_A] & 0x80)
		{
			m_pos.x += 100 * _GD->m_dt;
		}
		else if (_GD->m_keyboardState[DIK_D] & 0x80)
		{
			m_pos.x -= 100 * _GD->m_dt;
		}

		if (_GD->m_keyboardState[DIK_W] & 0x80)
		{
			m_pos.y += 100 * _GD->m_dt;
		}
		else if (_GD->m_keyboardState[DIK_S] & 0x80)
		{
			m_pos.y -= 100 * _GD->m_dt;
		}
	}
	m_transform =
		Matrix::CreateTranslation(Vector3(m_pos.x, m_pos.y, 0)) *
		Matrix::CreateRotationZ(m_rotation) *
		Matrix::CreateScale(Vector3(m_zoom, m_zoom, 1)) *
		Matrix::CreateTranslation(Vector3(0.0, 0.0f, 0.0f));

	GameObject2D::Tick(_GD);
}

void Camera2D::Draw(DrawData2D* _DD)
{

}