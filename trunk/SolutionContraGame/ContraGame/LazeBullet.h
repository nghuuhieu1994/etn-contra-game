#ifndef __LAZEBULLET_H__
#define __LAZEBULLET_H__

#include "Bullet.h"

class LazeBullet : public Bullet
{

public:
	LazeBullet();
	LazeBullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	~LazeBullet();
};

#endif