#ifndef __RAMBO_H__
#define __RAMBO_H__
#include "CObjectDx9.h"
#include "CInputDx9.h"

class Rambo : public Object
{
	Physic*			m_Physic;
public:
	Rambo();
	Rambo(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	Physic*			getPhysic() const { return m_Physic; }
	void Initialize();
	void HandleInput();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~Rambo();
};

#endif