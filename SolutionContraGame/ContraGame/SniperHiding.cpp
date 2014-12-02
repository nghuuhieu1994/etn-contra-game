#include "SniperHiding.h"

SniperHiding::SniperHiding()
{}

SniperHiding::SniperHiding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void SniperHiding::Shoot()
{
	switch (m_DirectAttack)
	{
	case AD_LEFT:
		if(m_CountBullet < 4)
		{
			if(m_TimeToShoot >= 1000)
			{
				BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, this->m_Position, D3DXVECTOR2(-2.0f, 0.0f), 0.0f);
				m_TimeToShoot = 0;
				++m_CountBullet;
			}

			m_TimeToShoot += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		}
		else
		{
			this->isShoot = false;
			m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
			m_CountBullet = 0;
		}
		break;
	case AD_RIGHT:
		if(m_CountBullet < 4)
		{
			if(m_TimeToShoot >= 1000)
			{
				BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, this->m_Position, D3DXVECTOR2(2.0f, 0.0f), 0.0f);
				m_TimeToShoot = 0;
				++m_CountBullet;
			}

			m_TimeToShoot += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		}
		else
		{
			this->isShoot = false;
			m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
			m_CountBullet = 0;
		}
		break;
		break;
	default:
		break;
	}
}

D3DXVECTOR3 SniperHiding::GetStartPositionOfBullet()
{
	switch(m_DirectAttack)
	{
	case AD_LEFT:
		return D3DXVECTOR3(m_Position.x + 40, m_Position.y + 24, 1);
		break;
	case AD_RIGHT:
		return D3DXVECTOR3(m_Position.x - 40, m_Position.y + 24, 1);
		break;
	default:
		break;	
	}
	return D3DXVECTOR3();
}

void SniperHiding::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive_hiding = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_HIDING));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_HIDING_EXPLOISION));
	m_Sprite = sprite_alive_hiding;
	isShoot = false;
	m_Position.z = 1.0f;
	m_CountBullet = 0;
}

void SniperHiding::UpdateAnimation()
{	
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		_distance_X = (int)(CGlobal::Rambo_X - getPositionVec2().x);
		if(_distance_X > 0)
		{
			m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeDirectAttack > 400)
			{
				m_DirectAttack = eDirectAttack::AD_RIGHT;
				m_Direction = eDirection::RIGHT;
				m_TimeChangeDirectAttack = 0;
			}
		}
		else
		{
			m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeDirectAttack > 400)
			{
				m_DirectAttack = eDirectAttack::AD_LEFT;
				m_Direction = eDirection::LEFT;
				m_TimeChangeDirectAttack = 0;
			}
		}
		m_Sprite->getAnimationAction()->setCurrentFrame(1);
		break;
	case STATE_SHOOTING:
		m_Sprite->getAnimationAction()->setCurrentFrame(0);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState >= 1000)
		{
			m_ObjectState = eObjectState::STATE_DEATH;
			m_TimeChangeState = 0;
		}
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}	
}


void SniperHiding::UpdateCollision(Object* checkingObject)
{
	if (!isDead)
	{
		if(checkingObject->getID() == eObjectID::BULLET_RAMBO)
		{
			IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

			if (collideDirection != IDDirection::DIR_NONE)
			{
				switch (checkingObject->getID())
				{
				case eObjectID::BULLET_RAMBO:
					if(m_ObjectState == eObjectState::STATE_SHOOTING)
					{
						checkingObject->setObjectState(eObjectState::STATE_DEATH);
						m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

void SniperHiding:: UpdateMovement()
{
}

void SniperHiding::Update()
{
	if(_distance_X < 300)
	{
		switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 5000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_SHOOTING;
				isShoot = true;
			}
			break;
		case STATE_SHOOTING:
			if(isShoot == true)
			{
				m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if (m_TimeChangeState > 2000)
				{
					m_TimeToShoot = 1000;
					Shoot();
					m_TimeChangeState = 0;
				}
			}
			break;
		case STATE_BEFORE_DEATH:
			if(isDead)
			{
				m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if(m_TimeChangeState > 1000)
				{
					m_ObjectState = eObjectState::STATE_DEATH;
					m_TimeChangeState = 0;
				}
			}
			break;
		case STATE_DEATH:
			this->Release();
			break;
		default:
			break;
		}
	}
	
}
void SniperHiding::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		if(m_Direction == eDirection::LEFT)
			m_Sprite->setSpriteEffect(ESpriteEffect::None);
		else
		{
			m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
		}
		m_Sprite->Render(spriteHandle, 
						getPositionVec2(), 
						m_Sprite->getSpriteEffect(), 
						m_Sprite->getRotate(), 
						m_Sprite->getScale(), 
						m_Position.z);
	}
}


void SniperHiding::Release()
{
	m_Sprite = 0;
	sprite_alive_hiding->Release();
	sprite_dead->Release();
	SAFE_DELETE(sprite_alive_hiding);
	SAFE_DELETE(sprite_dead);
}

SniperHiding::~SniperHiding()
{

}