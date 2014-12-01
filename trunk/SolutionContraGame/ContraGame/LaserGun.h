#ifndef __LASER_GUN_H__
#define __LASER_GUN_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class LaserGun : public DynamicObject
{
public:
	LaserGun();
	Physic*			getPhysic() const { return m_Physic; }
	LaserGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~LaserGun();
};

#endif