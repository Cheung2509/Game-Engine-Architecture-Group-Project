#ifndef  _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

#include <list>
#include "GameObject2D.h"
#include <memory>
#include "Room.h"
#include "Audio.h"

enum Direction
{
	NONE = 0,
	TOP = 1,
	RIGHT = 2,
	BOTTOM = 3,
	LEFT = 4
};

class Player2D;
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager() = default;

	void checkCollision(Room*);

	bool isCollided(GameObject2D*, GameObject2D*);

	void resolveCollision(Room*git , GameObject2D*, Direction);
private:
	Direction checkDirection(GameObject2D*, GameObject2D*);
	std::unique_ptr<AudioEngine> m_audioEngine;
	std::unique_ptr<SoundEffect> m_Pilons;
	bool thinCol = false;
};
#endif // ! _COLLISION_MANAGER_H_
