#ifndef __BOSS_PUNCH_H__
#define __BOSS_PUNCH_H__

#include "DynamicObject.h"
#include "Bullet.h"

class BossPunch : public DynamicObject
{
private:
	CSpriteDx9* spriteDead;
	CSpriteDx9*	spriteAlive;
	float		angle;
public:
	BossPunch();
	BossPunch(D3DXVECTOR3, eDirection, eObjectID);
	float geAngle() { return angle; }
	void setAngle(float ang){ angle = ang; }
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BossPunch();
};
#endif