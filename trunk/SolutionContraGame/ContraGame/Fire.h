#ifndef __FIRE_H__
#define __FIRE_H__

#include "DynamicObject.h"

class Fire : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
public:
	Fire();
	Fire(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Fire();
};

#endif