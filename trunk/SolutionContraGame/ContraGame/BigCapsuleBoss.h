#ifndef __BIG_CAPSULE_BOSS_H__
#define __BIG_CAPSULE_BOSS_H__

#include "DynamicObject.h"
#include <list>
#include "CapsuleBoss.h"
#include "BossBullet.h"

class BigCapsuleBoss : public DynamicObject
{
private:
	CSpriteDx9*	spriteAlive;
	CSpriteDx9*	spriteDead;
	bool isShoot;
	float mOpacity;
	int BulletCounter;	
	D3DXVECTOR3 listPosition[5];
public:
	list<CapsuleBoss*> m_ListEnemy;
	list<BossBullet*> m_ListBullet;
	BigCapsuleBoss();
	BigCapsuleBoss(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Shoot();
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BigCapsuleBoss();
};

#endif