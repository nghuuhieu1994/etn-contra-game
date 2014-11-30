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
	_isShoot = false;
	_isAddBullet = false;
	lastDirectAttack = eDirectAttack::NINE_CLOCK_DIRECTION;
	m_Position.z = 0.4f;
	m_AttackCounter = 8;
}

void BigGunRotating::Shoot()
{

	switch (m_DirectAttack)
	{
	case NINE_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, this->m_Position, D3DXVECTOR2(0.0f, 2.0f), 0);
		break;
	case TEN_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, this->m_Position, D3DXVECTOR2(0.0f, 2.0f), 0);
		break;
	case ELEVEN_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, this->m_Position, D3DXVECTOR2(0.0f, 2.0f), 0);
		break;
	default:
		break;
	}
}

D3DXVECTOR3 BigGunRotating::GetStartPositionOfBullet()
{
	switch (m_DirectAttack)
	{
	case NINE_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 30, m_Position.y, 1);
	case TEN_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 30, m_Position.y + 20, 1);
	case ELEVEN_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 20, m_Position.y + 30, 1);
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
		if(_distance_X > -250)
		{
			_isAddBullet = true;
				if (abs(_distance_Y) < 30)
		{
#pragma region MidAttack
			if (lastDirectAttack != eDirectAttack::NINE_CLOCK_DIRECTION)
			{
				m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if (m_TimeChangeDirectAttack > DELAY_TIME_GUN_ROTATE)
				{
					m_Sprite->getAnimationAction()->setIndexStart(6);
					m_Sprite->getAnimationAction()->setIndexEnd(8);
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
							m_Sprite->getAnimationAction()->setIndexStart(12);
							m_Sprite->getAnimationAction()->setIndexEnd(14);
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
							m_Sprite->getAnimationAction()->setIndexStart(9);
							m_Sprite->getAnimationAction()->setIndexEnd(11);
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
		}
		else
		{
			_isAddBullet = false;
			m_Sprite->getAnimationAction()->setIndexStart(0);
			m_Sprite->getAnimationAction()->setIndexEnd(5);
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

void BigGunRotating:: UpdateMovement()
{}
void BigGunRotating::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		if(_isAddBullet == true)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 3000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_SHOOTING;
				_isShoot = true;
			}
		}
		break;
	case STATE_SHOOTING:
		if(_isShoot == true)
		{
			Shoot();
			_isShoot = false;
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