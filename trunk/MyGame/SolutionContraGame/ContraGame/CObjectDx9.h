#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "CGlobal.h"
#include "CObjectStateDx9.h"

class ObjectState;
class Object
{	
	ObjectState* state;
	eObjectID m_eObjectID;
public:
	Object();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Render(SPRITEHANDLE spriteHandle);
	~Object();
};

#endif