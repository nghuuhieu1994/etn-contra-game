#ifndef __MACHINE_GUN_H__
#define __MACHINE_GUN_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class MachineGun : public DynamicObject
{
	//Physic*			m_Physic;
	D3DXVECTOR3		m_startPosition;
	CSpriteDx9* sprite_dead;
public:
	MachineGun();
	Physic*			getPhysic() const { return m_Physic; }
	MachineGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~MachineGun();
};

#endif