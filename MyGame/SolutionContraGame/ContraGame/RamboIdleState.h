#ifndef __RAMBO_IDLE_STATE_H__
#define __RAMBO_IDLE_STATE_H__
#include "CObjectStateDx9.h"
#include "SpriteManager.h"
#include "CInputDx9.h"
#include "RamboState.h"

class RamboIdleState : public RamboState
{
public:
	RamboIdleState();
	void UpdateAnimation();
	ObjectState* HandleInput(Object* hostObject);
	ObjectState* UpdateCollision(Object* hostObject, Object* checkingObject);
	ObjectState* UpdateMovement(Object* hostObject);
	void Render(SPRITEHANDLE spriteHandle);
	virtual ~RamboIdleState();
};

#endif