#ifndef __SNIPER_STANDING_H__
#define __SNIPER_STANDING_H__
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "Rambo.h"

class SniperStanding : public DynamicObject
{
private:
	CSpriteDx9* sprite_top;
	CSpriteDx9* sprite_bot;
	CSpriteDx9* sprite_mid;
	CSpriteDx9* sprite_dead;

	int _distance_X;
	int _distance_Y;
	bool isShoot;

	void Shoot();
	D3DXVECTOR3	GetStartPositionOfBullet();

	int countBullet;
public:
	SniperStanding();
	SniperStanding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~SniperStanding();
};


#endif