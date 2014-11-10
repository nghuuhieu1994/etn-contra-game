#ifndef __DEFAULT_BULLET_H__
#define __DEFAULT_BULLET_H__

#include "Bullet.h"

class DefaultBullet : public Bullet
{
public:
	DefaultBullet();
	DefaultBullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void UpdateMovement();
	~DefaultBullet();
};

#endif