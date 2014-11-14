#ifndef __ENEMYRUN_H__
#define __ENEMYRUN_H__

#include "DynamicObject.h"

class EnemyRun : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	bool isJumb;
	bool isDead;
public:
	EnemyRun();
	EnemyRun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~EnemyRun();
};

#endif