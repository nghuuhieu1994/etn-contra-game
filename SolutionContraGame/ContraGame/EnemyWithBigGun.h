#ifndef __ENEMY_WITH_BIG_GUN_H__
#define __ENEMY_WITH_BIG_GUN_H__

#include "DynamicObject.h"
#include "Rambo.h"

class EnemyWithBigGun : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	void Shoot();
public:
	EnemyWithBigGun();
	EnemyWithBigGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~EnemyWithBigGun();
};

#endif