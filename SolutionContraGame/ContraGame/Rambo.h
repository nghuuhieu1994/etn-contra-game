#ifndef __RAMBO_H__
#define __RAMBO_H__

#include "DynamicObject.h"
#include "CInputDx9.h"
#include "RamboSprite.h"

#include "Bullet.h"
#include "BulletPool.h"
#include "BulletPoolManager.h"

#include <list>

using namespace std;
class Rambo : public DynamicObject
{
private:
	bool HandleInputShooting();
	bool isAddBullet();
	bool isFall;
	bool isJump;
	bool isLieDown;
	bool isSetVelocityDeathState;
	bool isInvulnerable;
	unsigned char m_colorAlpha;
	int m_inverseColorAlpha;
	D3DXVECTOR3 GetStartPositionOfBullet();
	eIDSkillBullet m_SkillBullet;
	float m_maxPositionY;
	float m_timeAddBullet;
	float m_timeClimb;
	float m_timeDeath;
	float m_timeDelayRunAndShootRun;
	float m_timeWaterBomb;
	float m_timeBeforeDeadBottom;
	int m_timeInvulnerable;
	int UpdateInvulnerableAnimation();
	int HandleInputAimBottomRightState();
	int HandleInputAimTopRightState();
	int HandleInputAimUpState();
	int HandleInputBeforeDieState();
	int HandleInputClimbState();
	int HandleInputDeadState();
	int HandleInputDiveState();
	int HandleInputIdleState();
	int HandleInputJumpState();
	int HandleInputLieState();
	int HandleInputRunState();
	int HandleInputShootRunState();
	int HandleInputSwimShootState();
	int HandleInputSwimShootTopRightState();
	int HandleInputSwimShootUpState();
	int HandleInputSwimState();
	int HandleInputWaterBombState();
	int m_life;
	list<Object*> m_objectBelowCurrent;
	list<Object*> m_objectBelowPrevious;
	Object* m_ignoreCollisionObject;
	RamboSprite* m_RamboSprite;
	RECT m_RectangleCheckingObjectBelow;

	float prePosX;
	float finalPosX;

	void SetFallFlag();
	void SetVelocityXZero();
	int CheckOutBottomCamera();
	void SetVelocityYZero();
	void Shoot();
public:
	int getRamboLife(){ return m_life; }
	int UpdateCollisionTileBase(IDDirection collideDirection, Object* checkingObject);
	Rambo();
	void SetInvulnerable(bool para){ this->isInvulnerable = para;};
	Rambo(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	RECT getBound();
	virtual ~Rambo();
	void CleanIgnoreList();
	void HandleInput();
	void Initialize();
	void Release();
	void Render(SPRITEHANDLE spriteHandle);
	void SetFlag();
	void setRectangleCheckingObjectBelow();
	void setRamboLife(int _life){ m_life = _life; }
	void setSkillBullet(eIDSkillBullet _skillBullet){ this->m_SkillBullet = _skillBullet; };
	eIDSkillBullet getSkillBullet(){ return m_SkillBullet; };
	void Update();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void UpdatePreviousIgnoreList();
};

#endif