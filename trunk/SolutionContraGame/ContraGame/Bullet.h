#ifndef __BULLET_H__
#define __BULLET_H__

#include "DynamicObject.h"

class Bullet : public DynamicObject
{
private:
	eIDTypeBullet m_TypeBullet;
public:
	eIDTypeBullet getTypeBullet() const{return m_TypeBullet;};

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

