#ifndef __BOSS_ARM_H__
#define __BOSS_ARM_H__

#include "DynamicObject.h"
#include "Bullet.h"

class BossArm : public DynamicObject
{
private:
	CSpriteDx9* spriteDead;
	CSpriteDx9*	spriteAlive;
	float		angle;
public:
	BossArm();
	BossArm(D3DXVECTOR3, eDirection, eObjectID);
	float geAngle() { return angle; }
	void setAngle(float ang){ angle = ang; }
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BossArm();
};

#endif