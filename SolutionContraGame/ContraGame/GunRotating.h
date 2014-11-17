#ifndef __GUN_ROTATING_H__
#define __GUN_ROTATING_H__
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "Rambo.h"

class GunRotating : public DynamicObject
{
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_alive;
	int _distance_X;
	int _distance_Y;
	bool isShoot;

	void Shoot();
	D3DXVECTOR3	GetStartPositionOfBullet();
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