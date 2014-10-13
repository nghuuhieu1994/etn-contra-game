#ifndef __SNIPER_STANDING_H__
#define __SNIPER_STANDING_H__
#include "CObjectDx9.h"
#include "CInputDx9.h"
#include "Rambo.h"

class SniperStanding : public Object
{
private:
	CSpriteDx9* sprite_top;
	CSpriteDx9* sprite_bot;
	CSpriteDx9* sprite_mid;
	CSpriteDx9* sprite_dead;
	CSpriteDx9* Bullet[15];
	bool		m_canAttack;
	Physic*			m_Physic;
	int Rambo_X;
	int Rambo_y;
public:
	SniperStanding();
	SniperStanding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~SniperStanding();
};


#endif