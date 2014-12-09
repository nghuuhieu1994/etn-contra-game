#ifndef __BULLETBOSS1_H__
#define __BULLETBOSS1_H__

#include "Bullet.h"

class BulletBoss1 : public Bullet
{
private:
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_alive_move;
public:
	BulletBoss1();
	BulletBoss1(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	void UpdateAnimation();
	void Update();
	void UpdateCollision(Object* checkingObject);
	~BulletBoss1();
};

#endif