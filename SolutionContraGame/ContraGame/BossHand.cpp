#include "BossHand.h"

#ifndef VELOC_POPUP_X 
#define VELOC_POPUP_X 0.5f
#endif

#ifndef VELOC_POPUP_Y
#define VELOC_POPUP_Y 1.0f
#endif

BossHand::BossHand(){  }

BossHand::BossHand(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : DynamicObject(_position, _direction, _objectID)
{ 

}

BossHand::~BossHand(){}

void BossHand::Initialize()
{
	m_ObjectState = eObjectState::STATE_POPUP;
	isPopupDone = false;
	this->m_CountRotation = 0;
	this->m_AngleOfTarget = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		mArm[i] = new BossArm(m_Position, m_Direction, eObjectID::ROSHAN_ARM, m_Position, 0.1f);
		mArm[i]->Initialize();
	}

	mPunch = new BossPunch(m_Position, m_Direction, eObjectID::ROSHAN_PUNCH, m_Position);
	mPunch->Initialize();

	#pragma region. Init for arm of hand

	/*mArm[0] = new BossArm(m_Position, eDirection::RIGHT, eObjectID::ROSHAN_ARM, m_Position, 0.1f);
	mArm[0]->Initialize();
	mArm[0]->setAngleVeclocity(0.0f);
	mArm[0]->setAngle(0.0f);

	mArm[1] = new BossArm(D3DXVECTOR3(m_Position.x + 32, m_Position.y + 16, 1.0f), eDirection::RIGHT, eObjectID::ROSHAN_ARM, m_Position, 0.1f);
	mArm[1]->Initialize();
	mArm[1]->setAngleVeclocity(4.0f);
	mArm[1]->setAngle(30.0f);

	mArm[2] = new BossArm(D3DXVECTOR3(m_Position.x + 64, m_Position.y + 32, 1.0f), eDirection::RIGHT, eObjectID::ROSHAN_ARM, D3DXVECTOR3(m_Position.x + 32, m_Position.y + 16, 1.0f), 0.1f);
	mArm[2]->Initialize();
	mArm[2]->setAngleVeclocity(-60.0f);

	mArm[3] = new BossArm(D3DXVECTOR3(m_Position.x + 96, m_Position.y + 48, 1.0f), eDirection::RIGHT, eObjectID::ROSHAN_ARM, D3DXVECTOR3(m_Position.x + 64, m_Position.y + 32, 1.0f), 0.1f);
	mArm[3]->Initialize();
	mArm[3]->setAngleVeclocity(-50.0f);

	mPunch = new BossPunch(D3DXVECTOR3(m_Position.x + 128, m_Position.y + 64, 1.0f), m_Direction, m_eObjectID, D3DXVECTOR3(m_Position.x + 96, m_Position.y + 48, 1.0f));
	mPunch->Initialize();
	mPunch->setAngleVeclocity(-40.0f);
	*/
	//#pragma endregion
}

/*
	- Trạng thái của tay gồm có 3 trạng thái cơ bản:
		+ Popup: Mọc ra cái tay
		+ Xoay vòng tròn xuôi, sau đó xoay ngược
		+ Chĩa tay vào Rambo

		Sau 1 delta time nhất định thì bắn ra 1 bullet --> Cái này để tao làm cũng được.
		Việc mày làm là tích hợp action của 4 cái Arm và 1 cái Punch vào Object BossHand này.
		Sao cho khi gọi: BossHand->Update()... là được
*/

void BossHand::UpdateAnimation()
{
	if (mPunch){
		mPunch->UpdateAnimation();
	}
	if (mArm[0])
	{
		for (int i = 0; i < 4; i++)
		{
			mArm[i]->UpdateAnimation();
		}
	}

	switch (m_ObjectState)
	{
	case STATE_POPUP:
		break;
	case STATE_ALIVE_MOVE:
	case STATE_ALIVE_MOVE_A_LINE:
		if (mPunch->getObjectState() == STATE_BEFORE_DEATH)
		{
			for (int i = 0; i < 4; i++)
			{
				mArm[i]->setObjectState(STATE_BEFORE_DEATH);
			}
			m_ObjectState = STATE_BEFORE_DEATH;
		}
		break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
		{
			isDead = true;
		}
		break;
	case STATE_DEATH:
		break;
	}
}

void BossHand::UpdateCollision(Object* checkingObject)
{
	if (isDead == false)
	{
		for (int i = 0; i < 4; i++)
		{
			mArm[0]->UpdateCollision(checkingObject);
		}
		mPunch->UpdateCollision(checkingObject);
	}
}

void BossHand::UpdateMovement()
{

	switch (m_ObjectState)
	{
	case STATE_POPUP:
#pragma region. ARM_LEFT
		if (isPopupDone == false)
		{
			if (m_Direction == eDirection::RIGHT)
			{
				mPunch->getPhysic()->setVelocityX(VELOC_POPUP_X);
			}
			else
			{
				mPunch->getPhysic()->setVelocityX(-VELOC_POPUP_X);
			}
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

			if (Distance(mArm[1], mArm[0]) >= 32)
			{
				isPopupDone = true;
				mPunch->getPhysic()->setVelocity(D3DXVECTOR2(0, 0));
				mPunch->getPhysic()->setAccelerate(D3DXVECTOR2(0, 0));
				for (int i = 0; i < 4; i++)
				{
					mArm[i]->getPhysic()->setVelocity(D3DXVECTOR2(0, 0));
					mArm[i]->getPhysic()->setAccelerate(D3DXVECTOR2(0, 0));
				}
				this->m_ObjectState = eObjectState::STATE_ALIVE_MOVE;

			}

			for (int i = 0; i < 4; i++)
			{
				mArm[i]->UpdateMovement();
			}
			mPunch->UpdateMovement();

			if (this->m_ObjectState == eObjectState::STATE_ALIVE_MOVE)
			{
				mArm[0]->setAngleVeclocity(0.0f);
				mArm[0]->setAngle(0.0f);

				mArm[1]->setPositionOfOring(mArm[0]->getPositionVec3());
				if (m_Direction == eDirection::RIGHT)
				{
					mArm[1]->setAngleVeclocity(4.0f);
					mArm[1]->setAngle(85.0f);

					mArm[2]->setAngleVeclocity(-40.0f);
					mArm[3]->setAngleVeclocity(-50.0f);

					mPunch->setAngleVeclocity(-50.0f);
				}
				else
				{
					mArm[1]->setAngleVeclocity(-4.0f);
					mArm[1]->setAngle(95.0f);

					mArm[2]->setAngleVeclocity(40.0f);
					mArm[3]->setAngleVeclocity(50.0f);

					mPunch->setAngleVeclocity(50.0f);
				}
			}
		}
#pragma endregion
		break;
	case STATE_ALIVE_MOVE:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeState > 3200)
		{
			mArm[0]->setAngleVeclocity(-mArm[0]->getAngleVeclocity());
			mArm[1]->setAngleVeclocity(-mArm[1]->getAngleVeclocity());
			mArm[1]->setAngle(0);
			mArm[2]->setAngleVeclocity(-mArm[2]->getAngleVeclocity());
			mArm[3]->setAngleVeclocity(-mArm[3]->getAngleVeclocity());

			mPunch->setAngleVeclocity(-mPunch->getAngleVeclocity());
			m_TimeChangeState = 0.0f;
			++m_CountRotation;
			if (m_CountRotation == 2)
			{
				m_ObjectState = eObjectState::STATE_ALIVE_MOVE_A_LINE;
			}
		}

		for (int i = 1; i < 4; i++)
		{
			if (i > 1)
			{
				mArm[i]->setPositionOfOring(mArm[i - 1]->getPositionVec3());
				mArm[i]->setAngle(mArm[i - 1]->getAngle());
			}

			mArm[i]->UpdateMovement();
		}

		mPunch->setPositionOfOring(mArm[3]->getPositionVec3());
		mPunch->setAngle(mArm[3]->getAngle());
		mPunch->UpdateMovement();



		break;
	case eObjectState::STATE_ALIVE_MOVE_A_LINE:

		m_AngleOfTarget = atan2(-10, 10) * 180 / PI;

		if (mArm[1]->getAngle() > m_AngleOfTarget)
		{
			mArm[0]->setAngleVeclocity(-1.0f);
			mArm[1]->setAngleVeclocity(-1.0f);
			mArm[2]->setAngleVeclocity(-1.0f);
			mArm[3]->setAngleVeclocity(-1.0f);
			mPunch->setAngleVeclocity(-1.0f);
		}
		else if (mArm[1]->getAngle() < m_AngleOfTarget)
		{
			mArm[0]->setAngleVeclocity(10.0f);
			mArm[1]->setAngleVeclocity(10.0f);
			mArm[2]->setAngleVeclocity(10.0f);
			mArm[3]->setAngleVeclocity(10.0f);
			mPunch->setAngleVeclocity(10.0f);
		}

		for (int i = 1; i < 4; i++)
		{
			if (i > 1)
			{
				mArm[i]->setPositionOfOring(mArm[i - 1]->getPositionVec3());
				mArm[i]->setAngle(mArm[i - 1]->getAngle());
			}

			mArm[i]->UpdateMovement();
		}

		mPunch->setPositionOfOring(mArm[3]->getPositionVec3());
		mPunch->setAngle(mArm[3]->getAngle());
		mPunch->UpdateMovement();

		if ((int) mArm[1]->getAngle() <= m_AngleOfTarget + 5 && (int) mArm[1]->getAngle() >= m_AngleOfTarget - 5)
		{
			 m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
			//mPunch->setObjectState(STATE_BEFORE_DEATH);
		}

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
	case STATE_ALIVE_MOVE_A_LINE:		
		break;
	case STATE_BEFORE_DEATH:
		if (isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 1500)
			{
				m_ObjectState = STATE_DEATH;
				m_TimeChangeState = 0;
			}
		}
		break;
	case STATE_DEATH:
		Release();
		break;
	}
}

void BossHand::Render(SPRITEHANDLE spriteHandle)
{
	for (int i = 0; i < 4; i++)
	{
		if (mArm[i])
		{
			mArm[i]->Render(spriteHandle);
		}
	}
	if (mPunch)
	{
		mPunch->Render(spriteHandle);
	}
}

void BossHand::Release()
{
	if (mPunch)
	{
		mPunch->Release();
		SAFE_DELETE(mPunch);
	}
	if (mArm[0])
	{
		for (int i = 0; i < 4; i++)
		{
			mArm[i]->Release();
			SAFE_DELETE(mArm[i]);
		}
	}
}