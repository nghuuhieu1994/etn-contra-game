#ifndef __BOSS_MAP_ONE_H__
#define __BOSS_MAP_ONE_H__
#include "BossCenter.h"
#include "BossGun.h"
#include "SpriteManager.h"

class Tinker : DynamicObject
{
private:
	BossCenter*		m_Center;
	BossGun*		m_Left;
	BossGun*		m_Right;
	CSpriteDx9*		m_BossBody;

	float timeDelayGun;
	bool isDelay;

public:
	Tinker();
	Tinker(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Tinker();
};

#endif