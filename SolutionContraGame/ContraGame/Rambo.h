#ifndef __RAMBO_H__
#define __RAMBO_H__
#include "DynamicObject.h"
#include "CInputDx9.h"
#include "RamboSprite.h"
#include <list>

using namespace std;

class Rambo : public DynamicObject
{
	RamboSprite* m_RamboSprite;
	bool isJump;
	bool isLieDown;
	list<eObjectState> m_stackState;
public:
	Rambo();
	Rambo(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	virtual ~Rambo();
	void HandleInput();
	RECT getBound();
	void Initialize();
	void Release();
	void Render(SPRITEHANDLE spriteHandle);
	void Update();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
};

#endif