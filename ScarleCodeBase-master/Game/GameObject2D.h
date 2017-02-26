#ifndef _GAME_OBJECT_2D_H_
#define _GAME_OBJECT_2D_H_

//=================================================================
//the base Game Object 2D
//=================================================================

#include <d3d11_1.h>
#include "SimpleMath.h"
#include <string>
#include "ObjectType.h"

using namespace DirectX;
using namespace SimpleMath;
using namespace std;

struct GameData;
struct DrawData2D;

class GameObject2D
{
public:
	GameObject2D();
	virtual ~GameObject2D() {};

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD) = 0;
	// getters
	Vector2 GetPos() { return m_pos; }
	Vector2 GetVel() { return m_vel; }
	//setters

	void SetPos(Vector2 _pos) { m_pos = _pos; }
	void SetRot(float _rot) { m_rotation = _rot; }
	void SetColour(Color _colour) { m_colour = _colour; }
	void SetScale(Vector2 _scale) { m_scale = _scale; }
	void SetScale(float _scale) { m_scale = _scale * Vector2::One; }
	void SetOrigin(Vector2 _origin) { m_origin = _origin; }
	
	void		SetPhysicsOn(bool _physics) { m_physicsOn = _physics; }
	void		SetGravityOn(bool _gravity) { m_gravityOn = _gravity; }
	void		TogglePhysics() { m_physicsOn = !m_physicsOn; }
	void		ToggleGravity() { m_gravityOn = !m_gravityOn; }
	void		SetDrag(float _drag) { m_drag = _drag; }

	//ben changes
	ObjectType GetType();
	void setType(ObjectType type) { m_objectype = type; }
	bool isAlive() { return m_alive; }
	void SetAlive(bool alive) { m_alive = alive; }
	void addForce(Vector2 forceDirection) { m_vel += forceDirection; }

	//collisions
	bool checkCollisions(GameObject2D* _target) { return(Vector2::Distance(_target->GetPos(), m_pos) < 50.0f); }
	
protected:
	Vector2 m_pos;
	float m_rotation;
	Vector2 m_scale;
	Color m_colour;
	Vector2 m_origin;


	//physics stuff
	bool m_physicsOn = false;
	bool m_gravityOn = false;
	float m_drag = 0.0f;
	Vector2 m_vel = Vector2::Zero;
	Vector2 m_acc = Vector2::Zero;

	//changes

	ObjectType m_objectype = GAMEOBJECT;
	bool m_alive;
};
#endif