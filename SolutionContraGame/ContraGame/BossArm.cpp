#include "BossArm.h"

BossArm::BossArm() {}

BossArm::BossArm(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, D3DXVECTOR3 _positionOfOrigin, float _factorAngle)
: DynamicObject(_position, _direction, _objectID)
{
	m_PositionOfOrigin = _positionOfOrigin;
	angle = 0;
	factorAngle = _factorAngle;
	this->m_StartPosition = this->m_Position;
	deltaX = 0.0f;
	deltaY = 0.0f;
	isRootNode = false;
}

void BossArm::Initialize()
{
	m_AttackCounter = 0;
	spriteAlive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ARM_BOSS));
	spriteDead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	m_Sprite = spriteAlive;
}

void BossArm::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:

		break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
		{
			isDead = true;
			m_Sprite = spriteDead;
		}
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}

void BossArm::UpdateCollision(Object* checkingObject)
{
	if (!isDead)
	{
		if (checkingObject->getID() == eObjectID::BULLET_RAMBO)
		{
#pragma region BulletCollision
			IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
			if (collideDirection != IDDirection::DIR_NONE)
			{
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();				
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
		}
	}
}

void BossArm::UpdateMovement()
{
	//m_Physic->UpdateMovement(&m_Position);
	 
	//D3DXVECTOR3 tempPosition;

	//if(factorAngle != 0)
	//{
	//	tempPosition = D3DXVECTOR3((float)(this->m_PositionOfOrigin.x + factorR * cos(this->angle)), (float)(this->m_PositionOfOrigin.y + factorR * sin(this->angle)), 1.0f);
	//	/*this->getPhysic()->setVelocityX((float)(this->m_PositionOfOrigin.x + factorR * cos(this->angle) - this->m_Position.x));
	//	this->getPhysic()->setVelocityY((float)(this->m_PositionOfOrigin.y + factorR * sin(this->angle) - this->m_Position.y));*/
	//	deltaX = tempPosition.x - m_Position.x;
	//	deltaY = tempPosition.y - m_Position.y;
	//	this->m_Position = tempPosition;
	//}

	//if(angle >= 3.14 * 2)
	//{
	//	angle = 0;
	//}
	//angle += factorAngle;

	// xet van toc goc 

	float deltaTime = (float)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds() / 1000;
	deltaTime = deltaTime/((float)1/FRAME_RATE);
	angle += this->m_AngleVeclocity;

	//if(isRootNode == false)
	//{
	//	if(angleBlend> 2.8f)
	//	{
	//		angleBlend = 0.0f;
	//		this->m_StartPosition = this->m_Position;
	//		this->m_Position = D3DXVECTOR3((float)(100 + factorR * cos(this->angle)), (float)(100 + factorR * sin(this->angle)), 1.0f);
	//	}
		//else
		//{
			//angleBlend = angle;

	this->m_Position = D3DXVECTOR3((float)(m_PositionOfOrigin.x + 32 * cos(angle * PI / 180)), (float)(m_PositionOfOrigin.y + 32 * sin(angle * PI / 180)), 1.0f);

	//}
	//}
	//else
	//{
	//this->m_StartPosition = this->m_Position;
	//this->m_Position = D3DXVECTOR3((float)(100 + factorR * cos(this->angle)), (float)(100 + factorR * sin(this->angle)), 1.0f);
	//}
}

void BossArm::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		break;
	case STATE_BEFORE_DEATH:
		if (isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 1000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = STATE_DEATH;
			}
		}
		break;
	case STATE_DEATH:
		Release();
		break;
	default:
		break;
	}
}

void BossArm::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::None,
			angle,
			1.0f,
			m_Position.z);
	}
}

void BossArm::Release()
{
	m_Sprite = 0;
	spriteAlive->Release();
	spriteDead->Release();
	SAFE_DELETE(spriteAlive);
	SAFE_DELETE(spriteDead);
}

BossArm::~BossArm(){}