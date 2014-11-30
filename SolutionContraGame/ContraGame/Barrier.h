#ifndef __BARRIER_H__
#define __BARRIER_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class Barrier : public DynamicObject
{
	//Physic*			m_Physic;
	D3DXVECTOR3		m_startPosition;
	CSpriteDx9* sprite_dead;
public:
	Barrier();
	Physic*			getPhysic() const { return m_Physic; }
	Barrier(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~Barrier();
};

#endif