#ifndef __BULLETPOOL_H__
#define __BULLETPOOL_H__

#include "Bullet.h"
#include "DefaultBullet.h"
#include <vector>
#include <queue>

#define QUALITY_OF_DEFAULT_BULLET_RAMBO 20

class BulletPool
{
private:
	std::vector<std::queue<Bullet*>> m_BulletPool;
	BulletPool();
	~BulletPool();
public:
	static BulletPool* m_Instance;
	static BulletPool* getInstance();
	void Initialize();
	Bullet* popBulletFromBulletPool(eIDTypeBullet, D3DXVECTOR3, eDirectAttack);
	void addBulleToBulletPool(Bullet*);
	void releaseBulletPool();
};

#endif