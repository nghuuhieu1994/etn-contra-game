#include "BossBullet.h"

#ifndef ACCEL_Y_BULLET_BOSS
#define ACCEL_Y_BULLET_BOSS -0.005f
#endif

BossBullet::BossBullet()
{}

BossBullet::BossBullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{

}
BossBullet::~BossBullet(){}
void BossBullet::Initialize()
{
	m_AttackCounter = 1;
	spriteAlive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BOSS));
	spriteDead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_ObjectState = STATE_ALIVE_MOVE;
	m_Position.z = 1.0f;
	m_Sprite = spriteAlive;
	m_Physic->setAccelerate(D3DXVECTOR2(0, ACCEL_Y_BULLET_BOSS));
}

void BossBullet::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_BEFORE_DEATH:
		if (!isDead)
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

void BossBullet::UpdateCollision(Object* checkingObject)
{
	if (isDead == false)
	{
		if (checkingObject->getID() == BULLET_RAMBO)
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
					//if (m_AttackCounter >= 2)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						m_AttackCounter -= 2;
					}
				}
				else if (tempBullet->getTypeBullet() == eIDTypeBullet::FIRE_BULLET_OF_RAMBO)
				{
					//if (m_AttackCounter >= 4)
					{
						m_AttackCounter -= 4;
					}
				}

				if (m_AttackCounter <= 0)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					m_TimeChangeState = 0;
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
				}
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
#pragma endregion BulletCollision
		}
	}
}

void BossBullet::UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
}

void BossBullet::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeDirectAttack > 5000)
		{
			m_TimeChangeDirectAttack = 0;
			m_ObjectState = STATE_DEATH;
		}
		break;
	case STATE_BEFORE_DEATH:
		if (isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 1000)
			{
				m_ObjectState = eObjectState::STATE_DEATH;
				m_TimeChangeState = 0;
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

void BossBullet::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			m_Sprite->getSpriteEffect(),
			m_Sprite->getRotate(),
			m_Sprite->getScale(),
			m_Position.z);
	}
}

void BossBullet::Release()
{
	m_Sprite = NULL;
	if (spriteAlive)
	{
		spriteAlive->Release();
		SAFE_DELETE(spriteAlive);
	}
	if (spriteDead)
	{
		spriteDead->Release();
		SAFE_DELETE(spriteDead);
	}
}