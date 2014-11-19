#ifndef __BULLET_MOVING_STRAIGHT_H__
#define __BULLET_MOVING_STRAIGHT_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class GifBulletSinStraight : public DynamicObject
{
	//Physic*			m_Physic;
	D3DXVECTOR3		m_startPosition;
public:
	GifBulletSinStraight();
	Physic*			getPhysic() const { return m_Physic; }
	GifBulletSinStraight(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~GifBulletSinStraight();
	float Moving();
};

#endif