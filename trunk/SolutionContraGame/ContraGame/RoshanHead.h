#ifndef __ROSHAN_HEAD_H__
#define __ROSHAN_HEAD_H__

#include "DynamicObject.h"
#include "Bullet.h"
#include <list>
#include "BossBullet.h"

class RoshanHead : public DynamicObject
{
private:
	CSpriteDx9*	spriteAlive;
	CSpriteDx9*	spriteDead;
	bool isShoot;
	float mOpacity;
	list<BossBullet*> mListRoshanBullet;

public:
	RoshanHead();
	RoshanHead(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Shoot();
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~RoshanHead();
};

#endif
