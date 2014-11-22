#ifndef __ENEMY_RUN_SHOOTING_H__
#define __ENEMY_RUN_SHOOTING_H__

#include "DynamicObject.h"
#include "BulletPoolManager.h"

class EnemyRunShooting : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	bool isJumb;
	bool isShoot;
	bool isDead;
	void Shoot();
	D3DXVECTOR3	GetStartPositionOfBullet();
public:
	EnemyRunShooting();
	EnemyRunShooting(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~EnemyRunShooting();
};

#endif