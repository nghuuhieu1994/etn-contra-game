#include "BossHand.h"

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
		mArm[i] = new BossArm(m_Position, m_Direction, m_eObjectID);
		mArm[i]->Initialize();
	}
	m_ObjectState = STATE_POPUP;
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
	for (int i = 0; i < 4; i++)
	{
		mArm[0]->UpdateCollision(checkingObject);
	}
	mPunch->UpdateCollision(checkingObject);
}

void BossHand::UpdateMovement()
{

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