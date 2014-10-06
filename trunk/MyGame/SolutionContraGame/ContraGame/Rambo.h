#ifndef __RAMBO_H__
#define __RAMBO_H__
#include "CGlobal.h"
#include "CObjectDx9.h"
#include "CObjectStateDx9.h"
#include "RamboIdleState.h"

class Rambo : public Object
{
	RamboState* state;
public:
	Rambo();
	void HandleInput();
	D3DXVECTOR3 getPosition()const { return state->getPhysic()->getPositionVec3();}
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Render(SPRITEHANDLE spriteHandle);
	virtual ~Rambo();
};

#endif