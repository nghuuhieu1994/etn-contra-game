#include "BossPunch.h"

BossPunch::BossPunch(){}
BossPunch::BossPunch(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, D3DXVECTOR3 _positionOfOrigin)
: DynamicObject(_position, _direction, _objectID)
{
	this->m_PositionOfOrigin = _positionOfOrigin;
	angle = 0.0f;
	this->m_AngleVeclocity = -100.0f;
}

void BossPunch::Initialize()
{
	m_AttackCounter = 100;
	spriteAlive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_PUNCH_BOSS));
	spriteDead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	m_Sprite = spriteAlive;
}

void BossPunch::UpdateAnimation()
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

void BossPunch::UpdateCollision(Object* checkingObject)
{
	if (!isDead)
	{
		if (checkingObject->getID() == eObjectID::BULLET_RAMBO)
		{
#pragma region BulletCollision
			IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
			if (collideDirection != IDDirection::DIR_NONE)
			{
				Bullet* tempBullet = (Bullet*) (checkingObject);
				if (tempBullet->getTypeBullet() == eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO)
				{
					if (m_AttackCounter > 0)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						--m_AttackCounter;
					}
				}
				else if (tempBullet->getTypeBullet() == eIDTypeBullet::RED_BULLET_OF_RAMBO)
				{
					checkingObject->setObjectState(eObjectState::STATE_DEATH);
					if (m_AttackCounter >= 2)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						m_AttackCounter -= 2;
					}
				}
				else if (tempBullet->getTypeBullet() == eIDTypeBullet::FIRE_BULLET_OF_RAMBO)
				{
					if (m_AttackCounter >= 4)
					{
						m_AttackCounter -= 4;
					}
				}

				if (m_AttackCounter <= 0)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
				}
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
		}
	}
}

void BossPunch::UpdateMovement()
{
	if(this->m_AngleVeclocity != -100.0f)
	{
	float deltaTime = (float)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds() / 1000;
	deltaTime = deltaTime/((float)1/FRAME_RATE);
	angle += this->m_AngleVeclocity;

	this->m_Position = D3DXVECTOR3((float)(m_PositionOfOrigin.x + 32 * cos(angle * PI / 180)), (float)(m_PositionOfOrigin.y + 32 * sin(angle * PI / 180)), 1.0f);
	}
	else
	{
		this->getPhysic()->UpdateMovement(&m_Position);
	}
}

void BossPunch::Update()
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

void BossPunch::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		angle += 0.2f;
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			ESpriteEffect::None,
			angle,
			1.0f,
			m_Position.z);
	}
}

void BossPunch::Release()
{
	m_Sprite = 0;
	spriteAlive->Release();
	spriteDead->Release();
	SAFE_DELETE(spriteAlive);
	SAFE_DELETE(spriteDead);
}

BossPunch::~BossPunch()
{

}