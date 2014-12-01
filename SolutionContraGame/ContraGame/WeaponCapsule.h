#ifndef __WEAPON_CAPSULE_H__
#define __WEAPON_CAPSULE_H__
#include "DynamicObject.h"
#include "Barrier.h"
#include "FlameGun.h"
#include "LaserGun.h"
#include "MachineGun.h"
#include "RapidFire.h"
#include "SpreadGun.h"
#include "WeaponryManager.h"

class WeaponCapsule : public DynamicObject
{
	CSpriteDx9*		m_deadSprite;
	EIDWeaponry		m_IDWeaponry;
public:
	WeaponCapsule();
	Physic*			getPhysic() const { return m_Physic; }
	WeaponCapsule(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, EIDWeaponry idWeaponry);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~WeaponCapsule();
};

#endif