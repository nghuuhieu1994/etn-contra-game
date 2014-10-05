#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "CGlobal.h"
#include "CObjectStateDx9.h"

class ObjectState;
class Object
{	
protected:
	ObjectState* state;
	eObjectID m_eObjectID;
	eDirection m_Direction;
public:
	Object();
	Object(D3DXVECTOR3 _position, eDirection _direction, ObjectState* _state);
	virtual void UpdateCollision(Object* checkingObject);
	virtual void UpdateMovement();
	virtual void Render(SPRITEHANDLE spriteHandle);
	virtual ~Object();
};

#endif