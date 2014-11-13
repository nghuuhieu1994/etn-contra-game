#ifndef __BULLET_H__
#define __BULLET_H__

#include "DynamicObject.h"
#include "EIDTypeBullet.h"
#include "EDirectAttack.h"

class Bullet : public DynamicObject
{
protected:
	eIDTypeBullet m_TypeBullet;
	D3DXVECTOR3 m_StartPosition;
	float m_livingTime;
	float m_factor;
public:
	eIDTypeBullet getTypeBullet() const{return m_TypeBullet;};
	void setDirectAttack(eDirectAttack _directAttack){ this->m_DirectAttack = _directAttack;};
	void setStartPosition(D3DXVECTOR3 _position){ this->m_StartPosition = _position;};
	void setFactor(float _factor){ this->m_factor = _factor;};
	
	void ResetLivingTime();
	Bullet();
	Bullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	virtual ~Bullet();
	virtual void Initialize() = 0;
	virtual void reset();
	void Release();
	void Render(SPRITEHANDLE spriteHanlde);
	void Update();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	virtual void UpdateMovement() = 0;
};

#endif

