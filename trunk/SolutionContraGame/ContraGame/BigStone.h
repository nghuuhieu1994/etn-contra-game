#ifndef _STONE_H_
#define _STONE_H_

#include "DynamicObject.h"
#include "Bullet.h"
#include "CCamera.h"

class BigStone: public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
	CSpriteDx9* sprite_exploision;
	bool m_isJump;
	bool m_flag;
	int m_TimeToJump;
	D3DXVECTOR3 m_StartPosition;
	int _distanceX;
public:
	BigStone();
	BigStone(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	D3DXVECTOR3 getStartPostion()const{ return this->m_StartPosition;};
	void setStartPosition(D3DXVECTOR3 _startPosition) { this->m_StartPosition = _startPosition;};
	void Initialize();
	void Update();
	void UpdateAnimation();
	void UpdateMovement();
	void UpdateCollision(Object* checkingObject);
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BigStone();
	
};
#endif
