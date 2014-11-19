#ifndef ___ROCK_FALLINGH__
#define __ROCK_FALLING_H__

#include "DynamicObject.h"

class RockFalling: public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_dead;
public:
	RockFalling();
	RockFalling(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~RockFalling();
};

#endif