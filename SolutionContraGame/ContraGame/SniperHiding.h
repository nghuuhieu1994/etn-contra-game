#ifndef __SNIPER_HIDING_H_
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
	//CSpriteDx9* sprite_alive_shooting;
	int _distance_X;
	int m_timeAddBullet;
	bool isShoot;

	bool isAddBullet();
	void Shoot();
	D3DXVECTOR3	GetStartPositionOfBullet();

public:
	SniperHiding ();
	//Physic*			getPhysic() const { return m_Physic; }
	SniperHiding (D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~SniperHiding ();
};
#endif