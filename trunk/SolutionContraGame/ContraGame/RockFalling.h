#ifndef _ROCK_FALLING_H_
#define _ROCK_FALLING_H_

#include "DynamicObject.h"
#include "Bullet.h"

class RockFalling: public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_exploision;
	bool m_isJump;
public:
	RockFalling();
	RockFalling(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void Update();
	void UpdateAnimation();
	void UpdateMovement();
	void UpdateCollision(Object* checkingObject);
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~RockFalling();
	
};
#endif
