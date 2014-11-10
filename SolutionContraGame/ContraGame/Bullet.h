#ifndef __BULLET_H__
#define __BULLET_H__

#include "DynamicObject.h"
#include "EIDTypeBullet.h"
#include "EDirectAttack.h"

class Bullet : public DynamicObject
{
protected:
	eIDTypeBullet m_TypeBullet;
	eDirectAttack m_DirectAttack;
	D3DXVECTOR3 m_StartPosition;
	float m_livingTime;
public:
	eIDTypeBullet getTypeBullet() const{return m_TypeBullet;};
	void setDirectAttack(eDirectAttack _directAttack){ this->m_DirectAttack = _directAttack;};
	void setStartPosition(D3DXVECTOR3 _position){ this->m_StartPosition = _position;};
	void reset();
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
	virtual void UpdateMovement();
};

#endif

