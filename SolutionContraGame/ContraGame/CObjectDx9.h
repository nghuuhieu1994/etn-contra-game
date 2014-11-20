#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "EObjectState.h"
#include "EObjectID.h"
#include "CSpriteDx9.h"
#include "CPhysicDx9.h"
#include "ETypeObject.h"
#include "IDDirection.h"
#include "EDirection.h"
#include "EDirectAttack.h"
#include "SpriteManager.h"
#include "SoundMangerDx9.h"
#include "Box.h"
#include <d3dx9.h>
#include <d3d9.h>

//class Physic;

class Object
{
protected:
	eObjectID		m_eObjectID;
	eDirection		m_Direction;
	CSpriteDx9*		m_Sprite;
	eObjectState	m_ObjectState;
	ETypeObject		m_TypeObject;
	float			m_TimeChangeState;
	float			m_TimeChangeDirectAttack;
	int				m_AttackCounter;
	static int		m_identifyNumber;
	int				m_ObjectIdentifyNumber;
	D3DXVECTOR3		m_Position;

	//bit 0 -> Update Sprite
	//bit 1 -> Update Animation
	//bit 2 -> Update Movement
	//bit 3 -> Available
	//bit 4 -> Available
	//bit 5 -> Available
	//bit 6 -> Available
	//bit 7 -> Available
	char			m_UpdateFlag;
public:
	Object();
	Object(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	CSpriteDx9*		getSprite() const { return m_Sprite; }

	int				getIdentifyNumber(){ return this->m_identifyNumber; }

	void			setPosition(D3DXVECTOR3 _position){ m_Position = _position; }
	void			setPositionX(float _X){ m_Position.x = _X;}
	void			setPositionY(float _Y){ m_Position.y = _Y;}

	D3DXVECTOR3		getPositionVec3(){ return m_Position; }
	D3DXVECTOR2		getPositionVec2(){ return D3DXVECTOR2(m_Position.x, m_Position.y); }

	
	eObjectID		getID() const { return m_eObjectID; }
	ETypeObject		getTypeObject() const { return m_TypeObject; }

	eObjectState	getObjectState() const {return m_ObjectState;}
	virtual RECT getBound();
	virtual void Initialize() = 0;
	virtual void UpdateAnimation() = 0;

	virtual void UpdateCollision(Object* checkingObject) = 0;

	virtual void Update() = 0;
	virtual void Render(SPRITEHANDLE spriteHandle) = 0;
	virtual void Release() = 0;

	virtual ~Object();
};

#endif