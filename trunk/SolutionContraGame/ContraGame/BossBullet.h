#ifndef __BOSS_BULLET_H__
#define __BOSS_BULLET_H__

#include "DynamicObject.h"
#include "Bullet.h"
class BossBullet : public DynamicObject
{
private:
	CSpriteDx9* spriteAlive;
	CSpriteDx9*	spriteDead;
public:
	BossBullet();
	BossBullet(D3DXVECTOR3, eDirection, eObjectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object*);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BossBullet();
};

#endif
