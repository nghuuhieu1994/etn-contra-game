#ifndef __SNIPER_STANDING_H__
#define __SNIPER_STANDING_H__
#include "CObjectDx9.h"
#include "CInputDx9.h"

class SniperStanding : public Object
{
private:
	CSpriteDx9* sprite_top;
	CSpriteDx9* sprite_bot;
	CSpriteDx9* sprite_mid;
	CSpriteDx9* sprite_dead;
public:
	SniperStanding();
	SniperStanding(D3DXVECTOR3 _position, eDirection _direction);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~SniperStanding();
};


#endif