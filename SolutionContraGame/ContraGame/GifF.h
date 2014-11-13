#ifndef __GIF_F_H__
#define __GIF_F_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class GifF : public DynamicObject
{
	//Physic*			m_Physic;
	D3DXVECTOR3		m_startPosition;
	CSpriteDx9* sprite_dead;
public:
	GifF();
	Physic*			getPhysic() const { return m_Physic; }
	GifF(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~GifF();
};

#endif