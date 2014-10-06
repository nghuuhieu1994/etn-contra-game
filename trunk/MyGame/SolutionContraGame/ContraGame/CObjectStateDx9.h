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
	virtual void UpdateAnimation() = 0;
	virtual ObjectState* UpdateCollision(Object* hostObject, Object* checkingObject) = 0;
	virtual ObjectState* UpdateMovement(Object* hostObject) = 0;
	virtual void Render(SPRITEHANDLE spriteHandle) = 0;
	virtual ~ObjectState();
};

#endif