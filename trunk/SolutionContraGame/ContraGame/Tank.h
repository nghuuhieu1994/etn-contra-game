#ifndef __TANK_H__
#define __TANK_H__

#include "DynamicObject.h"
#include "BulletPoolManager.h"

class Tank : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
	bool m_isShoot;
	int m_distance_X;
	float GetAnpla();
	void Shoot();
	D3DXVECTOR3 GetStartPosition();
	int m_TimeToShoot;
	int m_CountBullet;
public:
	Tank();
	Tank(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Tank();
};

#endif