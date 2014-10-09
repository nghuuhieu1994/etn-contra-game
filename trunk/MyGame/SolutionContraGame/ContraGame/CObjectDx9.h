#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "CGlobal.h"
#include "CSpriteDx9.h"
#include "CPhysicDx9.h"
#include "SpriteManager.h"
#include "SoundMangerDx9.h"
#include <d3dx9.h>
#include <d3d9.h>

class Physic;

class Object
{	
protected:
	eObjectID		m_eObjectID;
	eDirection		m_Direction;
	CSpriteDx9*		m_Sprite;
	Physic*			m_Physic;
	eObjectState	m_ObjectState;
	//bit 0 -> Update Sprite
	//bit 1 -> Update Animation
	//bit 2 -> Update Movement
	char			m_UpdateFlag;
public:
	Object();
	Object(D3DXVECTOR3 _position, eDirection _direction);
	CSpriteDx9*		getSprite() const { return m_Sprite; }
	Physic*			getPhysic() const { return m_Physic; }
	virtual void Initialize() = 0;
	virtual void UpdateAnimation() = 0;
	
	virtual void UpdateCollision(Object* checkingObject) = 0;
	virtual void UpdateMovement() = 0;
	virtual void Render(SPRITEHANDLE spriteHandle) = 0;
	virtual void Release() = 0;
	virtual ~Object();
};

#endif