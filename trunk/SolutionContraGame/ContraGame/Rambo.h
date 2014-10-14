#ifndef __RAMBO_H__
#define __RAMBO_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class Rambo : public DynamicObject
{
	//Physic*			m_Physic;
public:
	//Physic*			getPhysic() const { return m_Physic; }
	Rambo();
	Rambo(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	virtual ~Rambo();
	void HandleInput();
	void Initialize();
	void PrintState();
	void Release();
	void Render(SPRITEHANDLE spriteHandle);
	void Update();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
};

#endif