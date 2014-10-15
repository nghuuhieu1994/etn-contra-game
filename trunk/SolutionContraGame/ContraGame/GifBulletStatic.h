#ifndef __GIF_BULLET_STATIC_H__
#define __GIF_BULLET_STATIC_H__
#include "DynamicObject.h"
#include "CInputDx9.h"

class GifBulletStatic : public DynamicObject
{
	//Physic*			m_Physic;
	CSpriteDx9* sprite_dead;
	CSpriteDx9* sprite_alive;
public:
	GifBulletStatic();
	//Physic*			getPhysic() const { return m_Physic; }
	GifBulletStatic(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	virtual ~GifBulletStatic();
};

#endif