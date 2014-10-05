#ifndef __OBJECT_STATE_DX9__
#define __OBJECT_STATE_DX9__
#include "CGlobal.h"
#include "CSpriteDx9.h"
#include "CPhysicDx9.h"


class Physic;
class Object;
class CSpriteDx9;
class ObjectState
{
protected:
	CSpriteDx9* m_Sprite;
	Physic* m_Physic;
public:
	ObjectState();
	CSpriteDx9* getSprite()const {return m_Sprite;}
	Physic* getPhysic()const {return m_Physic;}
	virtual ObjectState* UpdateCollision(Object* hostObject, Object* checkingObject);
	virtual ObjectState* UpdateMovement(Object* hostObject);
	void Render(SPRITEHANDLE spriteHandle);
	virtual ~ObjectState();
};

#endif