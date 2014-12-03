#ifndef __MAGIC_ROCK_H__
#define __MGIC_ROCK_H__

#include "DynamicObject.h"

class MagicRock : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
public:
	MagicRock();
	MagicRock(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~MagicRock();
};

#endif