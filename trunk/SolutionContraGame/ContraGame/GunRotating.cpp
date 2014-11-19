#include "GunRotating.h"



GunRotating::GunRotating()
{

}

GunRotating::GunRotating(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
}

void GunRotating::Shoot()
{
	// type some fucking code to shoot 1 bullet to Game Screen
	//BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO, GetStartPositionOfBullet(), D3DXVECTOR2(1.0f, 3.0f), 1);
	switch (m_DirectAttack)
	{
	case ZERO_CLOCK_DIRECTION:
		break;
	case ONE_CLOCK_DIRECTION:
		break;
	case TWO_CLOCK_DIRECTION:
		break;
	case THREE_CLOCK_DIRECTION:
		break;
	case FOUR_CLOCK_DIRECTION:
		break;
	case FIVE_CLOCK_DIRECTION:
		break;
	case SIX_CLOCK_DIRECTION:
		break;
	case SEVEN_CLOCK_DIRECTION:
		break;
	case EIGHT_CLOCK_DIRECTION:
		break;
	case NINE_CLOCK_DIRECTION:
		break;
	case TEN_CLOCK_DIRECTION:
		break;
	case ELEVEN_CLOCK_DIRECTION:
		break;
	default:
		break;
	}
}

D3DXVECTOR3 GunRotating::GetStartPositionOfBullet()
{
	switch(m_DirectAttack)
	{
	case ZERO_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x, m_Position.y + 30, 1);
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
	case SIX_CLOCK_DIRECTION:
		return D3DXVECTOR3(m_Position.x, m_Position.y - 30, 1);
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
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		_distance_X = CGlobal::Rambo_X - this->getPositionVec2().x;
		_distance_Y = CGlobal::Rambo_Y - this->getPositionVec2().y;

		if (abs(_distance_Y) < 60)
		{
			if (_distance_X < 0)
			{
				m_Sprite->getAnimationAction()->setCurrentFrame(11);
				m_DirectAttack = eDirectAttack::NINE_CLOCK_DIRECTION;
			}
			else
			{
				m_Sprite->getAnimationAction()->setCurrentFrame(5);
				m_DirectAttack = eDirectAttack::THREE_CLOCK_DIRECTION;
			}
		}
		else
		{
			int Dx = abs(_distance_X);
			if (Dx > 350)
			{
				m_Sprite->getAnimationAction()->setIndexStart(0);
				m_Sprite->getAnimationAction()->setIndexEnd(1);
				m_Sprite->UpdateAnimation(1000);
			}
			else
			{
				if (Dx < 350 && Dx > 100)
				{
					if (_distance_X < 0)
					{
						if (_distance_Y > 0)
						{
							m_Sprite->getAnimationAction()->setCurrentFrame(12);
							m_DirectAttack = eDirectAttack::TEN_CLOCK_DIRECTION;
						}
						else
						{
							m_Sprite->getAnimationAction()->setCurrentFrame(10);
							m_DirectAttack = eDirectAttack::EIGHT_CLOCK_DIRECTION;
						}
					}
					else
					{
						if (_distance_Y > 0)
						{
							m_Sprite->getAnimationAction()->setCurrentFrame(4);
							m_DirectAttack = eDirectAttack::TWO_CLOCK_DIRECTION;
						}
						else
						{
							m_Sprite->getAnimationAction()->setCurrentFrame(6);
							m_DirectAttack = eDirectAttack::FOUR_CLOCK_DIRECTION;
						}
					}
				}

				if (Dx <= 100 && Dx > 50)
				{
					if (_distance_X < 0)
					{
						if (_distance_Y > 0)
						{
							m_Sprite->getAnimationAction()->setCurrentFrame(13);
							m_DirectAttack = eDirectAttack::ELEVEN_CLOCK_DIRECTION;
						}
						else
						{
							m_Sprite->getAnimationAction()->setCurrentFrame(9);
							m_DirectAttack = eDirectAttack::SEVEN_CLOCK_DIRECTION;
						}
					}
					else
					{
						if (_distance_Y > 0)
						{
							m_Sprite->getAnimationAction()->setCurrentFrame(3);
							m_DirectAttack = eDirectAttack::ONE_CLOCK_DIRECTION;
						}
						else
						{
							m_Sprite->getAnimationAction()->setCurrentFrame(7);
							m_DirectAttack = eDirectAttack::FIVE_CLOCK_DIRECTION;
						}
					}
				}

				if (Dx <= 50)
				{
					if (_distance_Y > 0)
					{
						m_Sprite->getAnimationAction()->setCurrentFrame(2);
						m_DirectAttack = eDirectAttack::ZERO_CLOCK_DIRECTION;
					}
					else
					{
						m_Sprite->getAnimationAction()->setCurrentFrame(8);
						m_DirectAttack = eDirectAttack::SIX_CLOCK_DIRECTION;
					}
				}
			}
		}

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
		if (abs(_distance_X) < 300)
		{
			// in sert shoot funx
		}
		break;
	case STATE_BEFORE_DEATH:
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 1500)
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