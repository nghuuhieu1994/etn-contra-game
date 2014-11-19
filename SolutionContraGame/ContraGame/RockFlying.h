#ifndef __ROCK_FLYING_H__
#define __ROCK_FLYING_H__

#include "DynamicObject.h"

class RockFlying : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
public:
	RockFlying();
	RockFlying(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~RockFlying();
};

#endif