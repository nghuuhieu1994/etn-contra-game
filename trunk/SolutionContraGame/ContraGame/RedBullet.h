#ifndef __REDBULLET_H__
#define __REDBULLET_H__

#include "Bullet.h"

class RedBullet : public Bullet
{
public:
	RedBullet();
	RedBullet(D3DXVECTOR3, eDirection, eObjectID);
	void Initialize();
	void UpdateMovement();
	~RedBullet();
};

#endif