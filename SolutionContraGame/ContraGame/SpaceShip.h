#ifndef __SPACE_SHIP_H__
#define __SPACE_SHIP_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class SpaceShip : public DynamicObject
{
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_alive;
	

public:
	SpaceShip();
	SpaceShip(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~SpaceShip();
};
#endif