#ifndef __RAMBO_STATE__
#define __RAMBO_STATE__
#include "CObjectStateDx9.h"

class RamboState : public ObjectState
{
public:
	RamboState();
	virtual ObjectState* HandleInput(Object* hostObject) = 0;
	~RamboState();
};

#endif