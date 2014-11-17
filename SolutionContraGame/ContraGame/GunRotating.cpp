#include "GunRotating.h"



GunRotating::GunRotating()
{

}

GunRotating::GunRotating(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
	//m_Position = _position;
}

void GunRotating::Shoot()
{
	switch (m_DirectAttack)
	{
	/*case NINE_CLOCK_DIRECTION:
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 0);
		break;
	case THREE_CLOCK_DIRECTION:
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), 0);
		break;
	case ZERO_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(0.0f, 2.0f), 100);
		break;
	case SIX_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(0.0f, -2.0f), 100); 
		break;
	case AD_TOP_LEFT:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), -1);
		break;
	case AD_TOP_RIGHT:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), 1);
		break;
	case AD_BOTTOM_LEFT:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 1);
		break;
	case AD_BOTTOM_RIGHT:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), -1);
		break;
	default:
		break;	*/
	case ONE_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(1.0f, 3.0f), 1);
		break;
	case FIVE_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(1.0f, -4.0f), -1);
		break;
	case SEVEN_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-0.9f, -11.0f), 1);
		break;
	case ELEVEN_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, -0.5f), -1);
		break;
	case NINE_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 0);
		break;
	case THREE_CLOCK_DIRECTION:
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), 0);
		break;
	case ZERO_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(0.0f, 2.0f), 100);
		break;
	case SIX_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(0.0f, -2.0f), 100); 
		break;
	case TEN_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-3.5f, 0.0f), -1);
		break;
	case TWO_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(1.5f, 4.0f), 1);
		break;
	case EIGHT_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(-2.0f, 0.0f), 1);
		break;
	case FOUR_CLOCK_DIRECTION:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(6.0f, 0.0f), -1);
		break;
	default:
		break;	
	}
}

D3DXVECTOR3 GunRotating::GetStartPositionOfBullet()
{
	switch(m_DirectAttack)
	{
	case ONE_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 5, m_Position.y + 20, 0);
		break;
	case TWO_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 15, m_Position.y + 5, 0);
		break;
	case FIVE_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 9 , m_Position.y -5 , 0); 
		break;
	case SEVEN_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 5, m_Position.y - 10 , 0); 
		break;
	case ELEVEN_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 15, m_Position.y + 30, 0);
		break;
	case NINE_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 8, m_Position.y , 0); 
		break;
	case THREE_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 8, m_Position.y, 0);
		break;
	case ZERO_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x, m_Position.y + 8, 0); 
		break;
	case SIX_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x, m_Position.y - 8, 0); 
		break;
	case TEN_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 20, m_Position.y + 10, 0);
		break;
	case EIGHT_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x - 15, m_Position.y  , 0); 
		break;
	case FOUR_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x + 15, m_Position.y , 0); 
		break;

	default:
		break;	
	}
}

void GunRotating::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GUN_ROTATING));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
}

void GunRotating::UpdateAnimation()
{	
	// tư tưởng thằng này:
	// Tính khoảng cách theo trục X, Y
	// Dựa vào Khoảng cách đó mà thực hiện set Frame hiện tại cho mỗi trường hợp:
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: // cant be attack by rambo bullet
		m_Sprite = sprite_alive;
		_distance_X = (int)(abs(CGlobal::Rambo_X - this->getPositionVec2().x));
		_distance_Y = (int)(CGlobal::Rambo_Y - this->getPositionVec2().y);

		if( _distance_X > 350)
		{
			m_Sprite->getAnimation()->setIndexStart(0);
			m_Sprite->getAnimation()->setIndexEnd(1);
		}
		else
		{
			if(_distance_X <= 300 && _distance_X > 200)
			{
				if(CGlobal::Rambo_X < getPositionVec2().x)
				{
					m_Sprite->getAnimation()->setIndexStart(2);
					m_Sprite->getAnimation()->setIndexEnd(2);
					m_Sprite->getAnimation()->setCurrentFrame(2);
					m_DirectAttack = eDirectAttack::NINE_CLOCK_DIRECTION;
				}
				else
				{
					m_Sprite->getAnimation()->setIndexStart(8);
					m_Sprite->getAnimation()->setIndexEnd(8);
					m_Sprite->getAnimation()->setCurrentFrame(8);
					m_DirectAttack = eDirectAttack::THREE_CLOCK_DIRECTION;
				}
			}
			else
			{
				if(_distance_X <= 300 && _distance_X > 100)
				{
					if(CGlobal::Rambo_X < getPositionVec2().x)
					{
						if(_distance_Y <= 0)
						{
							m_Sprite->getAnimation()->setIndexStart(13);
							m_Sprite->getAnimation()->setIndexEnd(13);
							m_Sprite->getAnimation()->setCurrentFrame(13);
							m_DirectAttack = eDirectAttack::EIGHT_CLOCK_DIRECTION;
						}
						else
						{
							m_Sprite->getAnimation()->setIndexStart(3);
							m_Sprite->getAnimation()->setIndexEnd(3);
							m_Sprite->getAnimation()->setCurrentFrame(3);
							m_DirectAttack = eDirectAttack::TEN_CLOCK_DIRECTION;
						}
					}
					else
					{
						if(_distance_Y <= 0)
						{
							m_Sprite->getAnimation()->setIndexStart(9);
							m_Sprite->getAnimation()->setIndexEnd(9);
							m_Sprite->getAnimation()->setCurrentFrame(9);
							m_DirectAttack = eDirectAttack::FOUR_CLOCK_DIRECTION;
						}
						else
						{
							m_Sprite->getAnimation()->setIndexStart(7);
							m_Sprite->getAnimation()->setIndexEnd(7);
							m_Sprite->getAnimation()->setCurrentFrame(7);
							m_DirectAttack = eDirectAttack::TWO_CLOCK_DIRECTION;
						}
					}
				}
				else
				{
					if(_distance_X <= 100 && _distance_X > 20)
					{
						if(CGlobal::Rambo_X < getPositionVec2().x)
						{
							if(_distance_Y <= 0)
							{
								m_Sprite->getAnimation()->setIndexStart(12);
								m_Sprite->getAnimation()->setIndexEnd(12);
								m_Sprite->getAnimation()->setCurrentFrame(12);
								m_DirectAttack = eDirectAttack::SEVEN_CLOCK_DIRECTION;
							}
							else
							{
								m_Sprite->getAnimation()->setIndexStart(4);
								m_Sprite->getAnimation()->setIndexEnd(4);
								m_Sprite->getAnimation()->setCurrentFrame(4);
								m_DirectAttack = eDirectAttack::ELEVEN_CLOCK_DIRECTION;
							}
						}
						else
						{
							if(_distance_Y <= 0)
							{
								m_Sprite->getAnimation()->setIndexStart(10);
								m_Sprite->getAnimation()->setIndexEnd(10);
								m_Sprite->getAnimation()->setCurrentFrame(10);
								m_DirectAttack = eDirectAttack::FIVE_CLOCK_DIRECTION;
							}
							else
							{
								m_Sprite->getAnimation()->setIndexStart(6);
								m_Sprite->getAnimation()->setIndexEnd(6);
								m_Sprite->getAnimation()->setCurrentFrame(6);
								m_DirectAttack = eDirectAttack::ONE_CLOCK_DIRECTION;
							}
						}
					}
					else
					{
						if(_distance_Y < 0)
						{
							m_Sprite->getAnimation()->setIndexStart(11);
							m_Sprite->getAnimation()->setIndexEnd(11);
							m_Sprite->getAnimation()->setCurrentFrame(11);
							m_DirectAttack = eDirectAttack::SIX_CLOCK_DIRECTION;
						}
						else
						{
							m_Sprite->getAnimation()->setIndexStart(5);
							m_Sprite->getAnimation()->setIndexEnd(5);
							m_Sprite->getAnimation()->setCurrentFrame(5);
							m_DirectAttack = eDirectAttack::ZERO_CLOCK_DIRECTION;
						}
					}
				}
			}

		}
		m_Sprite->UpdateAnimation(1000);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(120);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}	
}


void GunRotating::UpdateCollision(Object* checkingObject)
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

void GunRotating:: UpdateMovement()
{}
void GunRotating::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
			m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 3000 && _distance_X < 350)
			{
				m_TimeChangeState = 0;
				isShoot = true;
			}
			if(isShoot == true && _distance_X < 350)
			{
				Shoot();
				isShoot = false;
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

		break;
	case STATE_DEATH:
		this->Release();
		break;
	default:
		break;
	}
}
void GunRotating::Render(SPRITEHANDLE spriteHandle)
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


void GunRotating::Release()
{
	m_Sprite = 0;
	sprite_alive->Release();
	sprite_dead->Release();
}

GunRotating::~GunRotating()
{

}