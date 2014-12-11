#ifndef __BULLETSNIPPERWATERHIDING_H__
#define __BULLETSNIPPERWATERHIDING_H__

#include "Bullet.h"
#include "BulletPoolManager.h"
#include "DynamicObject.h"

class BulletSnipperWaterHiding : public DynamicObject
{
private:
	CSpriteDx9* m_sprite_main;
	CSpriteDx9* m_spite_dead;
	BulletBoss1* bullet1;
	BulletBoss1* bullet2;
	BulletBoss1* bullet3;
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