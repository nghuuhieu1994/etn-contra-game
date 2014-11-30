#ifndef __SNIPER_HIDING_H__
#define __SNIPER_HIDING_H__

#include "DynamicObject.h"
#include "CInputDx9.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "BulletPoolManager.h"

class SniperHiding : public DynamicObject
{
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_alive_hiding;
	int _distance_X;
	bool isShoot;
	void Shoot();
	D3DXVECTOR3	GetStartPositionOfBullet();
	int m_TimeToShoot;
	int m_CountBullet;
public:
	SniperHiding ();
	SniperHiding (D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~SniperHiding ();
};
#endif