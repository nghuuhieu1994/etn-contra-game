#ifndef __CAPSULE_BOSS_H__
#define __CAPSULE_BOSS_H__

// The mini enemies of bigBozzMap3

#include "DynamicObject.h"
#include "BulletPoolManager.h"

class CapsuleBoss : public DynamicObject
{
private:
	CSpriteDx9* spriteDead;
	CSpriteDx9*	spriteAlive;
	bool isFall;
	bool isChangeDirect;
public:
	CapsuleBoss();
	CapsuleBoss(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~CapsuleBoss();
};
#endif