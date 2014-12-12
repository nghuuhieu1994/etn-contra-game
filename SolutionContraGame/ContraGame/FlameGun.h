#ifndef __FLAME_GUN_H__
#define __FLAME_GUN_H__
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "Rambo.h"
class FlameGun : public DynamicObject
{
public:
	FlameGun();
	Physic*			getPhysic() const { return m_Physic; }
	FlameGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~FlameGun();
};

#endif