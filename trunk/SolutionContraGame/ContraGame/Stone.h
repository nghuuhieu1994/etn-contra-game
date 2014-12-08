#ifndef _STONE_H_
#define _STONE_H_

#include "DynamicObject.h"
#include "Bullet.h"

class Stone: public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_exploision;
	bool m_isJump;
	int m_TimeToJump;
	int m_TimeForUpdate;
	int flag;
public:
	Stone();
	Stone(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void Update();
	void UpdateAnimation();
	void UpdateMovement();
	void UpdateCollision(Object* checkingObject);
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Stone();
	
};
#endif
