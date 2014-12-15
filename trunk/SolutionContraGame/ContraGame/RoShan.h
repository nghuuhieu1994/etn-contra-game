#ifndef __ROSHAN_H__
#define __ROSHAN_H__

#include "DynamicObject.h"
#include "RoshanHead.h"
#include "BossHand.h"

class Roshan : public DynamicObject
{
private:
	CSpriteDx9*		spriteAlive;
	CSpriteDx9*		spriteDead;
	CSpriteDx9*		spriteExploision;
	float mOpacity;
public:
	BossHand*		mLeftHand;
	BossHand*		mRightHand;
	RoshanHead*		mRoshanHead;

public:
	Roshan();
	Roshan(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	//void Shoot();
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Roshan();
};
#endif