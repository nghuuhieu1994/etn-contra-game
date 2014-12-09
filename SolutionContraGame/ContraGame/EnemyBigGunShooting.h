#ifndef __ENEMY_BIG_GUN_H__
#define __ENEMY_BIG_GUN_H__

#include "DynamicObject.h"
#include "Bullet.h"
#include "BulletPoolManager.h"

class EnemyBigGunShooting : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	bool m_isShoot;
	void Shoot();
public:
	EnemyBigGunShooting();
	EnemyBigGunShooting(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~EnemyBigGunShooting();
};

#endif