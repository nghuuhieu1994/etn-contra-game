#ifndef __BOSS_CENTER_H__
#define __BOSS_CENTER_H__

#include "DynamicObject.h"
#include "CInputDx9.h"
#include "BulletPool.h"

class BossCenter : public DynamicObject
{
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_alive;
public:
	BossCenter();
	BossCenter(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~BossCenter();
};

#endif