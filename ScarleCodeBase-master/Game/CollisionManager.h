#ifndef  _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

#include <list>
#include "GameObject2D.h"
#include <memory>
#include "Room.h"

class Player2D;
class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void checkCollision(Room*);

	bool isCollided(GameObject2D*, GameObject2D*);

	void resolveCollision(Room*git , GameObject2D*);
private:
};
#endif // ! _COLLISION_MANAGER_H_
