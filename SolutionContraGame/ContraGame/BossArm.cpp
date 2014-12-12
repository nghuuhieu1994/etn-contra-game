#include "BossArm.h"

BossArm::BossArm() {}

BossArm::BossArm(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{
	angle = 0.0f;
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
				/*Bullet* tempBullet = (Bullet*) (checkingObject);
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
				*/
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
		}
	}
}

void BossArm::UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
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