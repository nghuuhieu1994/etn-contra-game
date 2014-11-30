#include "SniperStanding.h"

SniperStanding::SniperStanding()
{
}

SniperStanding::SniperStanding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void SniperStanding::Shoot()
{
	switch (m_DirectAttack)
	{
	case ONE_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(1.0f, 3.0f), 1);
		break;
	case FIVE_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(1.0f, -4.0f), -1);
		break;
	case SEVEN_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(-0.9f, -11.0f), 1);
		break;
	case ELEVEN_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, -0.5f), -1);
		break;
	case NINE_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 0);
		break;
	case THREE_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), 0);
		break;
	case ZERO_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(0.0f, 2.0f), 100);
		break;
	case SIX_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(0.0f, -2.0f), 100); 
		break;
	case TEN_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(-3.5f, 0.0f), -1);
		break;
	case TWO_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(1.5f, 4.0f), 1);
		break;
	case EIGHT_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 1);
		break;
	case FOUR_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(6.0f, 0.0f), -1);
		break;
	default:
		break;	
	}
}

D3DXVECTOR3 SniperStanding::GetStartPositionOfBullet()
{
	switch(m_DirectAttack)
	{
	case ONE_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 20, m_Position.y + 30, 1);
	case TWO_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 30, m_Position.y + 20, 1);
	case THREE_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 30, m_Position.y, 1);
	case FOUR_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 30, m_Position.y - 20, 1);
	case FIVE_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 20, m_Position.y - 30, 1);
	case SEVEN_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 20, m_Position.y - 30, 1);
	case EIGHT_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 30, m_Position.y - 20, 1);
	case NINE_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 30, m_Position.y, 1);
	case TEN_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 30, m_Position.y + 20, 1);
	case ELEVEN_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 20, m_Position.y + 30, 1);

	/*case AD_LEFT:
		return D3DXVECTOR3(m_Position.x - 8, m_Position.y + 20, 0); 
	case AD_RIGHT:
		return D3DXVECTOR3(m_Position.x + 8, m_Position.y + 20, 0);
	case AD_TOP_LEFT:
		return D3DXVECTOR3(m_Position.x - 10, m_Position.y + 25, 0);
	case AD_TOP_RIGHT:
		return D3DXVECTOR3(m_Position.x + 10, m_Position.y + 25, 0);
	case AD_BOTTOM_LEFT:
		return D3DXVECTOR3(m_Position.x - 15, m_Position.y  , 0); 
	case AD_BOTTOM_RIGHT:
		return D3DXVECTOR3(m_Position.x + 15, m_Position.y , 0); */
	default:
		break;	
	}
}

void SniperStanding::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_bot = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_BOT));
	sprite_top = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_TOP));
	sprite_mid = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_MID));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	m_Sprite = sprite_mid;
	m_Position.z = 0.4f;
}

void SniperStanding::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:

		_distance_X = CGlobal::Rambo_X - this->getPositionVec2().x;
		_distance_Y = CGlobal::Rambo_Y - this->getPositionVec2().y;

#pragma region AttackMid
		if(abs(_distance_Y) < 10)
		{
			m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeDirectAttack > 700)
			{
				m_TimeChangeDirectAttack = 0;

				m_Sprite = sprite_mid;
				if(_distance_X < 0)
				{
					m_DirectAttack = eDirectAttack::NINE_CLOCK_DIRECTION;
					m_Direction = eDirection::LEFT;
				}
				else
				{
					m_DirectAttack = eDirectAttack::THREE_CLOCK_DIRECTION;
					m_Direction = eDirection::RIGHT;
				}
			}
		}
#pragma endregion AttackMid
		else
		{

#pragma region TopLeftAttack
			if(_distance_X < 0 && _distance_Y > 0)
			{
				m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if(m_TimeChangeDirectAttack > 700)
				{
					m_TimeChangeDirectAttack = 0;
					m_Sprite = sprite_top;
					m_Direction = eDirection::LEFT;

					if( _distance_X + _distance_Y > 0)
					{
						m_DirectAttack = eDirectAttack::ELEVEN_CLOCK_DIRECTION;
					}
					else
					{
						m_DirectAttack = eDirectAttack::TEN_CLOCK_DIRECTION;
					}
				}
			}
#pragma endregion TopLeftAttack

#pragma region BotLeftAttack
			if(_distance_X < 0 && _distance_Y < 0)
			{
				m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if(m_TimeChangeDirectAttack > 700)
				{
					m_TimeChangeDirectAttack = 0;
					m_Sprite = sprite_bot;
					m_Direction = eDirection::LEFT;

					if( _distance_X - _distance_Y < 0)
					{
						m_DirectAttack = eDirectAttack::EIGHT_CLOCK_DIRECTION;
					}
					else
					{
						m_DirectAttack = eDirectAttack::SEVEN_CLOCK_DIRECTION;
					}
				}
			}
#pragma endregion BotLeftAttack

#pragma region BotRightAttack
			if(_distance_X > 0 && _distance_Y < 0)
			{
				m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if(m_TimeChangeDirectAttack > 700)
				{
					m_TimeChangeDirectAttack = 0;
					m_Sprite = sprite_bot;
					m_Direction = eDirection::RIGHT;

					if( _distance_X + _distance_Y > 0)
					{
						m_DirectAttack = eDirectAttack::FOUR_CLOCK_DIRECTION;
					}
					else
					{
						m_DirectAttack = eDirectAttack::FIVE_CLOCK_DIRECTION;
					}
				}
			}
#pragma endregion BotRightAttack

#pragma region TopRightAttack 
			if(_distance_X > 0 && _distance_Y > 0)
			{
				m_TimeChangeDirectAttack += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if(m_TimeChangeDirectAttack > 700)
				{
					m_Sprite = sprite_top;
					m_Direction = eDirection::RIGHT;

					if( _distance_X - _distance_Y < 0)
					{
						m_DirectAttack = eDirectAttack::ONE_CLOCK_DIRECTION;
					}
					else
					{
						m_DirectAttack = eDirectAttack::TWO_CLOCK_DIRECTION;
					}
					m_TimeChangeDirectAttack = 0;
				}
			}
#pragma endregion TopRightAttack 
		}
		break;
	case STATE_SHOOTING:
		m_Sprite->UpdateAnimation(1000);
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
void SniperStanding::UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
}
void SniperStanding::UpdateCollision(Object* checkingObject)
{
	if( !isDead )
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

		if(collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
				case eObjectID::TILE_BASE:
					if (collideDirection == IDDirection::DIR_TOP)
					{
						this->m_Physic->setVelocityY(0);
					}
					break;
				default:
					break;
			}
		}
	}
}

void SniperStanding::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		//m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		//if(m_TimeChangeState > 10000)
		//{
		//	m_TimeChangeState = 0;
		//	m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
		//	isShoot = true;
		//}
		break;
	case STATE_SHOOTING:
		/*if(isShoot == true && _distance_X < 300)
		{
			Shoot();
			isShoot = false;
		}
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 2500)
		{
			m_TimeChangeState = 0;			
			m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
		}*/
		break;
	case STATE_BEFORE_DEATH:
		isDead = true;
		if(isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 1500)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_DEATH;
			}
		}
		break;
	case STATE_DEATH:
		this->Release();
		break;
	}
}

void SniperStanding::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		if(m_Direction == eDirection::LEFT)
			m_Sprite->setSpriteEffect(ESpriteEffect::None);
		else
		{
			m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
		}
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}
void SniperStanding::Release()
{
	m_Sprite = 0;
	sprite_bot->Release();
	sprite_dead->Release();
	sprite_top->Release();
	sprite_mid->Release();
}
SniperStanding::~SniperStanding()
{

}