#ifndef __BULLETBOSS1_H__
#define __BULLETBOSS1_H__

#include "Bullet.h"

class BulletBoss1 : public Bullet
{
public:
	BulletBoss1();
	BulletBoss1(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	~BulletBoss1();
};

#endif