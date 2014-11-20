#include "BigGunRotating.h"

BigGunRotating::BigGunRotating()
{

}

BigGunRotating::BigGunRotating(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
}

void BigGunRotating::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BIG_GUN_ROATING));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
	isShoot = false;
}

void BigGunRotating::Shoot()
{

	switch (m_DirectAttack)
	{
	case AD_TOP:
		break;
	case AD_LEFT:
		break;
	case AD_TOP_LEFT:
		break;
	default:
		break;
	}
}

D3DXVECTOR3 BigGunRotating::GetStartPositionOfBullet()
{
	switch (m_DirectAttack)
	{
	case AD_TOP:
	case AD_LEFT:
	case AD_TOP_LEFT:
	default:
		break;
	}
	return D3DXVECTOR3();
}

void BigGunRotating::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: // cant be attack by rambo bullet
		_distance_X = CGlobal::Rambo_X - m_Position.x;
		_distance_Y = CGlobal::Rambo_Y - m_Position.y;
		
		if (abs(_distance_Y) < 60)
		{
			m_Sprite->getAnimationAction()->setIndexStart(0);
			m_Sprite->getAnimationAction()->setIndexEnd(2);
			m_DirectAttack = eDirectAttack::AD_LEFT;
		}
		else
		{
			if (abs(_distance_X) >= 300)
			{
				m_Sprite->getAnimationAction()->setIndexStart(0);
				m_Sprite->getAnimationAction()->setIndexEnd(2);
				m_DirectAttack = eDirectAttack::AD_LEFT;
			}
			if (abs(_distance_X) < 300 && abs(_distance_X) > 100 && _distance_Y > 0)
			{
				m_Sprite->getAnimationAction()->setIndexStart(3);
				m_Sprite->getAnimationAction()->setIndexEnd(5);
				m_DirectAttack = eDirectAttack::AD_TOP_LEFT;
			}
			if (abs(_distance_X) < 100 && _distance_Y > 0)
			{
				m_Sprite->getAnimationAction()->setIndexStart(6);
				m_Sprite->getAnimationAction()->setIndexEnd(8);
				m_DirectAttack = eDirectAttack::AD_TOP;
			}
		}
		m_Sprite->UpdateAnimation(400);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(300);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}	
}


void BigGunRotating::UpdateCollision(Object* checkingObject)
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

void BigGunRotating:: UpdateMovement()
{}
void BigGunRotating::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:

		// type somefucking code to release 1 bullet on screen
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
void BigGunRotating::Render(SPRITEHANDLE spriteHandle)
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


void BigGunRotating::Release()
{
	m_Sprite = 0;
	sprite_alive->Release();
	sprite_dead->Release();
}

BigGunRotating::~BigGunRotating()
{

}