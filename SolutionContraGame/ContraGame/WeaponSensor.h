#ifndef __GIF_BULLET_STATIC_H__
#define __GIF_BULLET_STATIC_H__
#include "DynamicObject.h"
#include "Barrier.h"
#include "FlameGun.h"
#include "LaserGun.h"
#include "MachineGun.h"
#include "RapidFire.h"
#include "SpreadGun.h"
#include "WeaponryManager.h"
class WeaponSensor : public DynamicObject
{
	eObjectID		m_IDWeapon;
	CSpriteDx9*		sprite_dead;
	CSpriteDx9*		sprite_alive;
public:
	WeaponSensor();
	WeaponSensor(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, eObjectID idWeaponry);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~WeaponSensor();
};

#endif