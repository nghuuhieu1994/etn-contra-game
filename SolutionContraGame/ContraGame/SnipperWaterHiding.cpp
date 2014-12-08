#include "SnipperWaterHiding.h"

SnipperWaterHiding::SnipperWaterHiding()
{}

SnipperWaterHiding::SnipperWaterHiding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
}

void SnipperWaterHiding::Shoot()
{
	BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 3.0f), 100);
}

D3DXVECTOR3 SnipperWaterHiding::GetStartPositionOfBullet()
{
	return D3DXVECTOR3(m_Position.x, m_Position.y + 8, 0); 
}

void SnipperWaterHiding::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive_hiding = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_WATER_HIDING));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive_hiding;
	isShoot = false;
	m_Position.z = 0.4f;
}

void SnipperWaterHiding::UpdateAnimation()
{	
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite->getAnimationAction()->setCurrentFrame(0);
		break;
	case STATE_SHOOTING:
		m_Sprite->getAnimationAction()->setCurrentFrame(1);
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


void SnipperWaterHiding::UpdateCollision(Object* checkingObject)
{
	if (isDead != true)
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
						this->m_TimeChangeState = 0;
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

void SnipperWaterHiding:: UpdateMovement()
{
}

void SnipperWaterHiding::Update()
{
	if(CGlobal::Rambo_Y > m_Position.y)
	{
		switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 2000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_SHOOTING;
				isShoot = true;
			}
			break;
		case STATE_SHOOTING:
			if(isShoot == true)
			{
				Shoot();
				isShoot = false;
			}
			m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 1000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
			}
			break;
		case STATE_BEFORE_DEATH:
			m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 1000)
			{
				m_ObjectState = eObjectState::STATE_DEATH;
				m_TimeChangeState = 0;
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
void SnipperWaterHiding::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, 
						getPositionVec2(), 
						m_Sprite->getSpriteEffect(), 
						m_Sprite->getRotate(), 
						m_Sprite->getScale(), 
						m_Position.z);
	}
}


void SnipperWaterHiding::Release()
{
	m_Sprite = 0;
	sprite_alive_hiding->Release();
	sprite_dead->Release();
	SAFE_DELETE(sprite_alive_hiding);
	SAFE_DELETE(sprite_dead);
}

SnipperWaterHiding::~SnipperWaterHiding()
{

}