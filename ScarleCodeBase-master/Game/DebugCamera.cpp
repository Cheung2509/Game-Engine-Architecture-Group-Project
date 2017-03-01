#include "DebugCamera.h"
#include "gamedata.h"
#include "DrawData2D.h"
#include "helper.h"

DebugCamera::DebugCamera(Vector2 _target, float _zoom) : Camera2D(_target, _zoom)
{

}

DebugCamera::~DebugCamera()
{

}

void DebugCamera::Tick(GameData* _GD)
{
	if (_GD->m_GS == GS_PLAY_DEBUG_CAM)
	{
		if (_GD->m_keyboardState[DIK_A] & 0x80)
		{
			m_pos.x -= 200 * _GD->m_dt;
		}
		else if (_GD->m_keyboardState[DIK_D] & 0x80)
		{
			m_pos.x += 200 * _GD->m_dt;
		}

		if (_GD->m_keyboardState[DIK_W] & 0x80)
		{
			m_pos.y -= 200 * _GD->m_dt;
		}
		else if (_GD->m_keyboardState[DIK_S] & 0x80)
		{
			m_pos.y += 200 * _GD->m_dt;
		}
	}

	Camera2D::Tick(_GD);
}