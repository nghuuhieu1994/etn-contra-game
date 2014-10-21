﻿#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "DynamicObject.h"
#include "CGlobal.h"
#include "SweptAABB.h"

class DynamicObject;

static bool Intersect(const RECT *rect1, const RECT *rect2)
{
	if (rect1 == NULL || rect2 == NULL)
		return false;

	if (rect1->right < rect2->left) // _rect bên trái so với obj->_rect
		return false;
	if (rect1->left > rect2->right) // _rect bên phải so với obj->_rect
		return false;
	if (rect1->bottom > rect2->top) // _rect bên trên so với obj->_rect
		return false;
	if (rect1->top < rect2->bottom) // _rect bên dưới so với obj->_rect
		return false;

	return true;
}

static BOX ConvertToBox(RECT _Rect, float _vx = 0.0f, float _vy = 0.0f)
{
	BOX box(
		_Rect.left,
		_Rect.top,
		_Rect.right - _Rect.left,
		_Rect.top - _Rect.bottom,
		_vx,
		_vy
		);

	return box;
}

static BOX ConvertToBroadPhase(BOX _Box)
{
	return GetSweptBroadPhaseBox(_Box);
}

class Collision 
{
public:
	float m_MoveX, m_MoveY;
public:
	Collision();
	virtual void InitCollision();
	virtual IDDirection CheckCollision(DynamicObject *, Object *);
	//virtual IDDirection CheckCollision(CBaseObject *);
	//virtual void ResponeCollision(DynamicObject *, Object *) = 0;
	~Collision();
};

#endif