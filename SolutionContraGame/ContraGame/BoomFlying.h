#ifndef __BOOM_FLYING_H__
#define __BOOM_FLYING_H__

#include "DynamicObject.h"

class BoomFlying : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
public:
	BoomFlying();
	BoomFlying(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BoomFlying();
};

#endif