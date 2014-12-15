#ifndef __FIRE_BRIDGE_H__
#define __FIRE_BRIDGE_H__

#include "DynamicObject.h"
#include "Fire.h"

class FireBridge : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	int m_distanceY;
	//Fire* m_fire_1;
	//Fire* m_fire_2;
	//Fire* fireObject[2];

public:
	Fire* getFire1() const{ this->m_fire_1;};
	Fire* getFire2() const{ this->m_fire_2;};
		Fire* m_fire_1;
	Fire* m_fire_2;
	FireBridge();
	FireBridge(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~FireBridge();
};

#endif