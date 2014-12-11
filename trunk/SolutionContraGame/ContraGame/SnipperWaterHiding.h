#ifndef __SNIPER_WATER_HIDING_H_
#define __SNIPER_WATER_HIDING_H__
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "BulletPoolManager.h"
#include "BulletSnipperWaterHiding.h"

class SnipperWaterHiding : public DynamicObject
{
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_alive_hiding;
	//BulletSnipperWaterHiding* bullet;
	list<BulletSnipperWaterHiding*> m_ListBullet;

	int _distance_Y;
	int _distance_X;
	bool isShoot;
	void Shoot();
	D3DXVECTOR3	GetStartPositionOfBullet();

public:
	SnipperWaterHiding ();
	SnipperWaterHiding (D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~SnipperWaterHiding ();
};
#endif