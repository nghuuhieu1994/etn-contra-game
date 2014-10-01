#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "CGlobal.h"
#include "CSpriteDx9.h"
#include "CPhysicDx9.h"


class Object
{
	CSpriteDx9* m_Sprite;
	Physic* m_Physic;
public:
	Object();
	~Object();
};

#endif