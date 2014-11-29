#include "EnemyWithBigGun.h"

EnemyWithBigGun::EnemyWithBigGun()
{
}

EnemyWithBigGun::EnemyWithBigGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void EnemyWithBigGun::Shoot()
{
	//BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, D3DXVECTOR3(m_Position.x - 1, m_Position.y , 0), D3DXVECTOR2(-2.0f, 0.0f), 0);
}

void EnemyWithBigGun::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_WITH_BIG_GUN));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	m_Position.z = 0.4f;
	m_AttackCounter = 12;
}

void EnemyWithBigGun::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		this->m_Sprite->getAnimationAction()->setIndexStart(0);
		this->m_Sprite->getAnimationAction()->setIndexEnd(1);
		break;
	case STATE_BEFORE_DEATH: 
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void EnemyWithBigGun::UpdateCollision(Object* checkingObject)
{
	if( isDead != true )
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

		if(collideDirection != IDDirection::DIR_NONE)
		{
			if(checkingObject->getID() == eObjectID::BULLET_RAMBO)
			{
				Bullet* tempBullet = (Bullet*)(checkingObject);
				if(tempBullet->getTypeBullet() == eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO)
				{
					if(m_AttackCounter > 0)
					{
						--m_AttackCounter;
					}
				}
				else if(tempBullet->getTypeBullet() == eIDTypeBullet::RED_BULLET_OF_RAMBO)
				{
					if(m_AttackCounter >= 2)
					{
						m_AttackCounter -= 2;
					}
				}
				else if(tempBullet->getTypeBullet() == eIDTypeBullet::FIRE_BULLET_OF_RAMBO)
				{
					if(m_AttackCounter >= 4)
					{
						m_AttackCounter -= 4;
					}
				}

				if(m_AttackCounter == 0)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
				}
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
		}
	}
}
void EnemyWithBigGun::UpdateMovement()
{
}

void EnemyWithBigGun::Update()
{
	switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			break;
		case STATE_BEFORE_DEATH:
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 1500)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_DEATH;
			}
			break;
		case STATE_DEATH:
			this->Release();
			break;
		default:
			break;
		}
}

void EnemyWithBigGun::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != NULL)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void EnemyWithBigGun::Release()
{
	m_Sprite = 0;
	sprite_dead->Release();
	sprite_main->Release();
}
EnemyWithBigGun::~EnemyWithBigGun()
{
}