#include "GameObject2D.h"

class Sprite;

class Collectables: public GameObject2D
{
public:
	Collectables(Sprite*);
	~Collectables();
	bool GetPickedUp();
	void SetPickeduP();
	bool GetRespawnUp();
	void SetRespawnUp(bool RespawnUp) { m_RespawnUp = RespawnUp; }
	
	Sprite* getSprite() { return sprite; }

	virtual void Draw(DrawData2D* _DD);

private:
	bool PickedUp;
	bool m_RespawnUp = false;
	Sprite* sprite;
};
