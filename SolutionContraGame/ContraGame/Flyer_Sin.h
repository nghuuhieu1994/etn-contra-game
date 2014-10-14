#ifndef __FlyerSin_H__
#define __FlyerSin_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class Flyer_Sin : public DynamicObject
{
	//Physic*			m_Physic;
	D3DXVECTOR3		m_startPosition;
public:
	Flyer_Sin();
	Physic*			getPhysic() const { return m_Physic; }
	Flyer_Sin(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~Flyer_Sin();
	void Sin(D3DXVECTOR3& a);
};

#endif