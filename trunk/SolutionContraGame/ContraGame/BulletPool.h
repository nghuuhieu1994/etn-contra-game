#ifndef __BULLETPOOL_H__
#define __BULLETPOOL_H__

#include "Bullet.h"
#include "DefaultBullet.h"
#include "RedBullet.h"
#include "FireBullet.h"
#include <vector>
#include <queue>

#define QUALITY_OF_DEFAULT_BULLET_RAMBO 100
#define QUALITY_OF_RED_BULLET_RAMBO 100
#define QUALITY_OF_FIRE_BULLET_RAMBO 100

class BulletPool
{
private:
	std::vector<std::queue<Bullet*>> m_BulletPool;
	static BulletPool* m_Instance;
	BulletPool();
	~BulletPool();
public:
	static BulletPool* getInstance();
	void Initialize();
	Bullet* popBulletFromBulletPool(eIDTypeBullet, D3DXVECTOR3, D3DXVECTOR2, float);
	void addBulleToBulletPool(Bullet*);
	void releaseBulletPool();
};

#endif