#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "CGlobal.h"
#include "CObjectStateDx9.h"

class ObjectState;
class Object
{	
protected:
	eObjectID m_eObjectID;
	eDirection m_Direction;
public:
	Object();
	Object(D3DXVECTOR3 _position, eDirection _direction, ObjectState* _state);
	virtual void UpdateAnimation() = 0;
	virtual void UpdateCollision(Object* checkingObject) = 0;
	virtual void UpdateMovement() = 0;
	virtual void Render(SPRITEHANDLE spriteHandle) = 0;
	virtual ~Object();
};

#endif