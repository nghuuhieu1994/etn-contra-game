#include "BossHand.h"

#ifndef VELOC_POPUP_X 
#define VELOC_POPUP_X 0.5f
#endif

#ifndef VELOC_POPUP_Y
#define VELOC_POPUP_Y 1.0f
#endif

BossHand::BossHand(){  }

BossHand::BossHand(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
{ 

}

BossHand::~BossHand(){}

void BossHand::Initialize()
{
	mPunch = new BossPunch(m_Position, m_Direction, m_eObjectID);
	mPunch->Initialize();

	for (int i = 0; i < 4; i++)
	{
		mArm[i] = new BossArm(m_Position, m_Direction, m_eObjectID, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.1f);
		mArm[i]->Initialize();
	}

	m_ObjectState = STATE_POPUP;

	isPopupDone = false;
}

void BossHand::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_POPUP:
		break;
	case STATE_ALIVE_MOVE:
		break;
	case STATE_BEFORE_DEATH:
		break;
	case STATE_DEATH:
		break;
	}
}

void BossHand::UpdateCollision(Object* checkingObject)
{
	//for (int i = 0; i < 4; i++)
	//{
	//	mArm[0]->UpdateCollision(checkingObject);
	//}
	//mPunch->UpdateCollision(checkingObject);
}

void BossHand::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_POPUP:

		/*
		if (isPopupDone == false)
		{
			mPunch->getPhysic()->setVelocityX(VELOC_POPUP_X);
			mPunch->getPhysic()->setVelocityY(VELOC_POPUP_Y);
			if (Distance(mPunch, mArm[3]) >= 32)
			{
				mArm[3]->getPhysic()->setVelocityX(mPunch->getPhysic()->getVelocity().x);
				mArm[3]->getPhysic()->setVelocityY(mPunch->getPhysic()->getVelocity().y);
			}
			if (Distance(mArm[3], mArm[2]) > 32)
			{
				mArm[2]->getPhysic()->setVelocityX(mPunch->getPhysic()->getVelocity().x);
				mArm[2]->getPhysic()->setVelocityY(mPunch->getPhysic()->getVelocity().y);
			}
			if (Distance(mArm[2], mArm[1]) >= 32)
			{
				mArm[1]->getPhysic()->setVelocityX(mPunch->getPhysic()->getVelocity().x);
				mArm[1]->getPhysic()->setVelocityY(mPunch->getPhysic()->getVelocity().y);
			}

			if (Distance(mArm[1], mArm[0] ) >= 32)
			{
				isPopupDone = true;
				mPunch->getPhysic()->setVelocity(D3DXVECTOR2(0, 0));
				mPunch->getPhysic()->setAccelerate(D3DXVECTOR2(0, 0));
				for (int i = 0; i < 4; i++)
				{
					mArm[i]->getPhysic()->setVelocity(D3DXVECTOR2(0, 0));
					mArm[i]->getPhysic()->setAccelerate(D3DXVECTOR2(0, 0));
				}
			}



			for (int i = 0; i < 4; i++)
			{
				mArm[i]->UpdateMovement();
			}
			mPunch->UpdateMovement();
		}*/

		break;
	case STATE_ALIVE_MOVE:
		break;
	case STATE_BEFORE_DEATH:
		break;
	case STATE_DEATH:
		break;
	}
}

void BossHand::Update()
{
	switch (m_ObjectState)
	{
	case STATE_POPUP:
		break;
	case STATE_ALIVE_MOVE:
		break;
	case STATE_BEFORE_DEATH:
		break;
	case STATE_DEATH:
		break;
	}
}

void BossHand::Render(SPRITEHANDLE spriteHandle)
{
	for (int i = 0; i < 4; i++)
	{
		if (mArm[i])
		{
			mArm[0]->Render(spriteHandle);
		}
	}
	if (mPunch)
	{
		mPunch->Render(spriteHandle);
	}
}

void BossHand::Release()
{

}