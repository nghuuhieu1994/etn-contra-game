#ifndef __BULLETSNIPPERWATERHIDING_H__
#define __BULLETSNIPPERWATERHIDING_H__

#include "Bullet.h"
#include "BulletPoolManager.h"

class BulletSnipperWaterHiding : public Bullet
{
private:
	CSpriteDx9* m_sprite_main;
	CSpriteDx9* m_spite_dead;
	bool m_isDead;
	BulletSnipperWaterHiding* bullet1;
	BulletSnipperWaterHiding* bullet2;
	BulletSnipperWaterHiding* bullet3;
public:
	BulletSnipperWaterHiding();
	BulletSnipperWaterHiding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateMovement();
	void Update();
	void UpdateAnimation();
	//void UpdateMovement();
	~BulletSnipperWaterHiding();
};

#endif