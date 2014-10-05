#ifndef __RAMBO_IDLE_STATE_H__
#define __RAMBO_IDLE_STATE_H__
#include "CObjectStateDx9.h"
#include "SpriteManager.h"
class RamboIdleState : public ObjectState
{
public:
	RamboIdleState();

	ObjectState* UpdateCollision(Object* hostObject, Object* checkingObject);
	ObjectState* UpdateMovement(Object* hostObject);
	
	virtual ~RamboIdleState();
};

#endif