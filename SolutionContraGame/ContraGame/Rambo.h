#ifndef __RAMBO_H__
#define __RAMBO_H__
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "RamboMoveSprite.h"

class Rambo : public DynamicObject
{
	RamboSprite* m_RamboSprite;
public:
	Rambo();
	Rambo(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	virtual ~Rambo();
	void HandleInput();
	void Initialize();
	void Release();
	void Render(SPRITEHANDLE spriteHandle);
	void Update();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
};

#endif