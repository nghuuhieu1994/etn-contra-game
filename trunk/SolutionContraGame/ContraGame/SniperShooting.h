#ifndef __SNIPER_SHOOTING_H_
#define __SNIPER_SHOOTING_H__
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "BulletPoolManager.h"

class SniperShooting : public DynamicObject
{
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_alive;

	int _distance_Y;
	int _distance_X;
	bool isShoot;
	void Shoot();
	D3DXVECTOR3	GetStartPositionOfBullet();

public:
	SniperShooting ();
	SniperShooting (D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~SniperShooting();
};
#endif