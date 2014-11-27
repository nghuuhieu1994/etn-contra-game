#include "BigGunRotating.h"

BigGunRotating::BigGunRotating()
{

}

BigGunRotating::BigGunRotating(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void BigGunRotating::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BIG_GUN_ROATING));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
	isShoot = false;
	lastDirectAttack = eDirectAttack::NINE_CLOCK_DIRECTION;
	m_Position.z = 0.4f;
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
		if (abs(_distance_Y) < 30)
		{
#pragma region MidAttack
			if (lastDirectAttack != eDirectAttack::NINE_CLOCK_DIRECTION)
			{
				m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if (m_TimeChangeDirectAttack > DELAY_TIME_GUN_ROTATE)
				{
					m_Sprite->getAnimationAction()->setIndexStart(0);
					m_Sprite->getAnimationAction()->setIndexEnd(2);
					m_DirectAttack = eDirectAttack::AD_LEFT;
					m_TimeChangeDirectAttack = 0;
					lastDirectAttack = m_DirectAttack;
				}
			}
			else
			{
				m_TimeChangeDirectAttack = 0;
			}
#pragma endregion MidAttack
		}
		else
		{
			if (_distance_X < 0 && _distance_Y > 0)
			{
#pragma region TopLeftAttack
				if (_distance_X + _distance_Y > 0)
				{
					if (lastDirectAttack != eDirectAttack::ELEVEN_CLOCK_DIRECTION)
					{
						m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
						if (m_TimeChangeDirectAttack > DELAY_TIME_GUN_ROTATE)
						{
							m_DirectAttack = eDirectAttack::ELEVEN_CLOCK_DIRECTION;
							m_Sprite->getAnimationAction()->setIndexStart(6);
							m_Sprite->getAnimationAction()->setIndexEnd(8);
							m_TimeChangeDirectAttack = 0;
							lastDirectAttack = m_DirectAttack;
						}
					}
					else
					{
						m_TimeChangeDirectAttack = 0;
					}
				}
				else
				{
					if (lastDirectAttack != eDirectAttack::TEN_CLOCK_DIRECTION)
					{
						m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds(); 
						if (m_TimeChangeDirectAttack > DELAY_TIME_GUN_ROTATE)
						{
							m_DirectAttack = eDirectAttack::TEN_CLOCK_DIRECTION;
							m_Sprite->getAnimationAction()->setIndexStart(3);
							m_Sprite->getAnimationAction()->setIndexEnd(5);
							m_TimeChangeDirectAttack = 0;
							lastDirectAttack = m_DirectAttack;
						}
					}
					else
					{
						m_TimeChangeDirectAttack = 0;
					}
				}
#pragma endregion TopLeftAttack
			}
		}
		m_Sprite->UpdateAnimation(500);
		break;
	case STATE_SHOOTING:
		// !need animation shoot
		break;
	case STATE_BEFORE_DEATH:
		if (!isDead)
		{
			m_Sprite = sprite_dead;
			isDead = true;
		}
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
	if (!isDead)
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

		if (collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			default:
				break;
			}

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
		break;
	case STATE_SHOOTING:
		// some fucking code to shoot, then change to state_alive-idle
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