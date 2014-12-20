#ifndef __BOSS_HAND_H__
#define __BOSS_HAND_H__

#include "DynamicObject.h"
#include "BossArm.h"
#include "BossPunch.h"
#include "BossBullet.h"
#include <list>
class BossHand: public DynamicObject
{
private:
	BossArm*	mArm[4];
	bool	isPopupDone;
	int		m_CountRotation;
	float	m_AngleOfTarget;
	int		m_CountLineStatus;
public:
	list<BossBullet*> mListRoshanBullet;
	BossPunch*	mPunch;
	BossHand();
	BossHand(D3DXVECTOR3, eDirection, eObjectID);
	~BossHand();
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
};

#endif