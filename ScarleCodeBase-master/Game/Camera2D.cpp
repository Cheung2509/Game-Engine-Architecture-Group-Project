#include "Camera2D.h"
#include "gamedata.h"
#include "DrawData2D.h"
#include "helper.h"
#include <iostream>

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
	m_transform =
		Matrix::CreateTranslation(Vector3(-m_pos.x, -m_pos.y, 0)) *
		Matrix::CreateRotationZ(m_rotation) *
		Matrix::CreateScale(Vector3(m_zoom, m_zoom, 1)) *
		Matrix::CreateTranslation(Vector3(_GD->viewportWidth * 0.5f, _GD->viewportHeight * 0.5f, 0.0f));

	GameObject2D::Tick(_GD);
}

void Camera2D::Draw(DrawData2D* _DD)
{

}