#ifndef _BOOM_H_
#define _BOOM_H_

#include "DynamicObject.h"

class Boom: public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_exploision;
	float rotate;
	bool isPlaySound;
	D3DXVECTOR3 m_StartPosition;
public:
	Boom();
	Boom(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void Update();
	void UpdateAnimation();
	void UpdateMovement();
	void UpdateCollision(Object* checkingObject);
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Boom();
	
};
#endif
