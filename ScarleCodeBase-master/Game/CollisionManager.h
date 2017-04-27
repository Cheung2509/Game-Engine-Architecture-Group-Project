#ifndef  _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

#include <list>
#include "GameObject2D.h"

class Room;

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void checkCollision(std::list<GameObject2D*>, Room*);

	bool isCollided(GameObject2D*, GameObject2D*);

	void resolveCollision();
private:
	std::list<GameObject2D> m_collider;
};
#endif // ! _COLLISION_MANAGER_H_
