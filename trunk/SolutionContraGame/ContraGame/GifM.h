#ifndef __GIF_M_H__
#define __GIF_M_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class GifM : public DynamicObject
{
	//Physic*			m_Physic;
	D3DXVECTOR3		m_startPosition;
	CSpriteDx9* sprite_dead;
public:
	GifM();
	Physic*			getPhysic() const { return m_Physic; }
	GifM(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~GifM();
};

#endif