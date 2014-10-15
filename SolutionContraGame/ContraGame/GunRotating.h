#ifndef __GUN_ROTATING_H__
#define __GUN_ROTATING_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class GunRotating : public DynamicObject
{
	//Physic*			m_Physic;
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_alive;
public:
	GunRotating();
	//Physic*			getPhysic() const { return m_Physic; }
	GunRotating(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~GunRotating();
};

#endif