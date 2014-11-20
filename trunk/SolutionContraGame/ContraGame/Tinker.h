#ifndef __BOSS_MAP_ONE_H__
#define __BOSS_MAP_ONE_H__
#include "BossCenter.h"
#include "BossGun.h"
#include "SpriteManager.h"

class Tinker : DynamicObject
{
private:
	CSpriteDx9*		m_BodyAlive;
	CSpriteDx9*		m_BodyDeath;
	BossCenter*		m_Center;
	BossGun*		m_Left;
	BossGun*		m_Right;

	CSpriteDx9*		m_spriteExplosion[8]; // explo step by step .....
	bool isBurned;

	void BossExplosion();

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