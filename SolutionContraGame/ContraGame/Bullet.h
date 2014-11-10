#ifndef __BULLET_H__
#define __BULLET_H__

#include "DynamicObject.h"
#include "EIDTypeBullet.h"

class Bullet : public DynamicObject
{
private:
	eIDTypeBullet m_TypeBullet;
	float m_livingTime;
public:
	eIDTypeBullet getTypeBullet() const{return m_TypeBullet;};
	void ResetLivingTime();
	Bullet();
	Bullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	virtual ~Bullet();
	void Initialize();
	void Release();
	void Render(SPRITEHANDLE spriteHanlde);
	void Update();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
};

#endif

