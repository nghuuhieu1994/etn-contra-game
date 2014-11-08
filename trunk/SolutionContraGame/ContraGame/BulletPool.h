#ifndef __BULLETPOOL_H__
#define __BULLETPOOL_H__

#include "Bullet.h"
#include <vector>
#include <queue>

/// BulletPool contain
///	RAMBOBULLET => 20
/// 
///
///
///
///
///

#define BULLETOFRAMBO 20

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
	Bullet* popBulletFromBulletPool(eIDTypeBullet, D3DXVECTOR3, D3DXVECTOR2);
	void addBulleToBulletPool(Bullet*);
	void releaseBulletPool();
};

#endif