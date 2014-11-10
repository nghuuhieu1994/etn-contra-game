#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "DynamicObject.h"
#include "CGlobal.h"
#include "SweptAABB.h"



static bool Intersect(const RECT *rect1, const RECT *rect2)
{
	if (rect1 == 0 || rect2 == 0)
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
		(float)(_Rect.left),
		(float)(_Rect.top),
		(float)(_Rect.right - _Rect.left),
		(float)(_Rect.top - _Rect.bottom),
		(float)_vx,
		(float)_vy
		);

	return box;
}

static BOX ConvertToBroadPhase(BOX _Box)
{
	return GetSweptBroadPhaseBox(_Box);
}

class DynamicObject;
class Collision 
{
public:
	float m_MoveX, m_MoveY;
public:
	Collision();
	void InitCollision();
	IDDirection CheckCollision(DynamicObject *, Object *);
	~Collision();
};

#endif