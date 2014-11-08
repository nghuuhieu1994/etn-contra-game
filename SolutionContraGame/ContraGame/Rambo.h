#ifndef __RAMBO_H__
#define __RAMBO_H__

#include "DynamicObject.h"
#include "CInputDx9.h"
#include "RamboSprite.h"
#include <list>
#include "Bullet.h"
#include "BulletPool.h"
#include "BulletPoolManager.h"

using namespace std;

class Rambo : public DynamicObject
{
private:
	bool isFall;
	bool isJump;
	bool isLieDown;
	float m_maxPositionY;
	float m_timeClimb;
	float m_timeWaterBomb;
	list<Object*> m_objectBelowCurrent;
	list<Object*> m_objectBelowPrevious;
	Object*				m_ignoreCollisionObject;
	RamboSprite* m_RamboSprite;
	RECT	m_RectangleCheckingObjectBelow;

	int HandleInputAimBottomRightState();
	int HandleInputAimTopRightState();
	int HandleInputAimUpState();
	int HandleInputClimbState();
	int HandleInputIdleState();
	int HandleInputJumpState();
	int HandleInputLieState();
	int HandleInputRunState();
	int HandleInputShootRunState();
	int HandleInputSwimState();
	int HandleInputWaterBombState();
public:
	int UpdateCollisionTileBase(IDDirection collideDirection, Object* checkingObject);
	Rambo();
	Rambo(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	RECT getBound();
	virtual ~Rambo();
	void HandleInput();
	void Initialize();
	void Release();
	void Render(SPRITEHANDLE spriteHandle);
	void setRectangleCheckingObjectBelow();
	void Update();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
};

#endif