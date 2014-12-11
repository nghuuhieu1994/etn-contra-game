#ifndef __BULLETSNIPPERWATERHIDING_H__
#define __BULLETSNIPPERWATERHIDING_H__

#include "Bullet.h"
#include "BulletPoolManager.h"
#include "DynamicObject.h"

class BulletSnipperWaterHiding : public Bullet
{
private:
	CSpriteDx9* m_sprite_main;
	CSpriteDx9* m_spite_dead;
	BulletSnipperWaterHiding* bullet1;
	BulletSnipperWaterHiding* bullet2;
	BulletSnipperWaterHiding* bullet3;
	bool m_isDead;
	int m_TimeToBoom;
public:
	BulletSnipperWaterHiding();
	BulletSnipperWaterHiding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BulletSnipperWaterHiding();
};

#endif