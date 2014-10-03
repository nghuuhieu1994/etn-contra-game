#ifndef __OBJECT_STATE_DX9__
#define __OBJECT_STATE_DX9__
#include "CGlobal.h"
#include "CSpriteDx9.h"
#include "CPhysicDx9.h"

class ObjectState
{
	CSpriteDx9* m_Sprite;
	Physic* m_Physic;
public:
	ObjectState();
	~ObjectState();
};

#endif