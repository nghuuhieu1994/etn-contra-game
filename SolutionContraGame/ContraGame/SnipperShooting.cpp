#include "SniperShooting.h"

SniperShooting::SniperShooting()
{}

SniperShooting::SniperShooting(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{}

void SniperShooting::Shoot()
{
	switch (m_DirectAttack)
	{
	case AD_LEFT:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), 0);
		break;
	case AD_RIGHT:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 0);
		break;
	default:
		break;	
	}
}

D3DXVECTOR3 SniperShooting::GetStartPositionOfBullet()
{
	switch(m_DirectAttack)
	{
	case AD_LEFT:
		return D3DXVECTOR3(m_Position.x + 8, m_Position.y, 0);
		break;
	case AD_RIGHT:
		return D3DXVECTOR3(m_Position.x - 8, m_Position.y , 0); 
		break;
	default:
		break;	
	}
	return D3DXVECTOR3();
}

void SniperShooting::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_SHOOTING));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	isShoot = false;
}

void SniperShooting::UpdateAnimation()
{	
	if(CGlobal::Rambo_X < m_Position.x)
	{
		m_Direction = eDirection::LEFT;
		m_DirectAttack = eDirectAttack::AD_LEFT;
	}
	else
	{
		m_Direction = eDirection::RIGHT;
		m_DirectAttack = eDirectAttack::AD_RIGHT;
	}

	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: 
		m_Sprite = sprite_alive;
		m_Sprite->getAnimationAction()->setIndexStart(0);
		m_Sprite->getAnimationAction()->setIndexEnd(3);
		m_Sprite->UpdateAnimation(400);
		break;
	case STATE_SHOOTING:
		m_Sprite = sprite_alive;
		m_Sprite->getAnimationAction()->setIndexStart(4);
		m_Sprite->getAnimationAction()->setIndexEnd(5);
		m_Sprite->UpdateAnimation(400);
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
	if(m_Direction == eDirection::LEFT)
	{
		m_Sprite->setSpriteEffect(ESpriteEffect::None);
	}

	else
	{
		if(m_Direction == eDirection::RIGHT)
		{
			m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
		}
	}
}


void SniperShooting::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch (checkingObject->getID())
		{
			case eObjectID ::BULLET_RAMBO:
				m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
				break;
			default:
				break;
		}

	}
}

void SniperShooting:: UpdateMovement()
{
}

void SniperShooting::Update()
{
	_distance_X = abs(CGlobal::Rambo_X - this->getPositionVec2().x);
	if(_distance_X < 300)
	{
		switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 10000)
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
			if(m_TimeChangeState > 3000)
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
void SniperShooting::Render(SPRITEHANDLE spriteHandle)
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


void SniperShooting::Release()
{
	m_Sprite = 0;
	sprite_alive->Release();
	sprite_dead->Release();
}

SniperShooting::~SniperShooting()
{

}