#ifndef __WEAPON_CAPSULE_VER2_H__
#define __WEAPON_CAPSULE_VER2_H__
#include "DynamicObject.h"
#include "Barrier.h"
#include "FlameGun.h"
#include "LaserGun.h"
#include "MachineGun.h"
#include "RapidFire.h"
#include "SpreadGun.h"
#include "WeaponryManager.h"

class WeaponCapsuleVer2 : public DynamicObject
{
	CSpriteDx9*		m_deadSprite;
	eObjectID		m_IDWeaponry;
public:
	WeaponCapsuleVer2();
	Physic*			getPhysic() const { return m_Physic; }
	WeaponCapsuleVer2(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, eObjectID idWeaponry);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~WeaponCapsuleVer2();
};

#endif