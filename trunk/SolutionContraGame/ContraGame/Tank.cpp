#include "Tank.h"

Tank::Tank()
{
}

Tank::Tank(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void Tank::Shoot()
{
	if(m_CountBullet < 4)
		{
			if(m_TimeToShoot >= 1000)
			{
				BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPosition(), D3DXVECTOR2(-1.0f, 0.0f), 0.0f);
				m_TimeToShoot = 0;
				++m_CountBullet;
			}

			m_TimeToShoot += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		}
		else
		{
			m_isShoot = false;
			m_CountBullet = 0;
		}
}

D3DXVECTOR3 Tank::GetStartPosition()
{
	switch (m_Sprite->getAnimationAction()->getCurrentIndex())
	{
	case 0:
	case 1:
	case 6:
	case 7:
	case 12:
	case 13:
	case 18:
    case 19:
		return D3DXVECTOR3(m_Position.x - 70, m_Position.y + 50, 1);
		break;
	case 2:
	case 3:
	case 8:
	case 9:
	case 14:
	case 15:
	case 20:
    case 21:
		return D3DXVECTOR3(m_Position.x - 60, m_Position.y + 35, 1);
		break;
	case 4:
	case 5:
	case 10:
	case 11:
	case 16:
	case 17:
	case 22:
    case 24:
		return D3DXVECTOR3(m_Position.x - 50, m_Position.y + 25, 1);
		break;

	default:
		break;
	}
}

void Tank::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_TANK));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	m_Position.z = 1.0f;
	m_Direction = eDirection::LEFT;
	m_AttackCounter = 24;
	m_Sprite->getAnimationAction()->setCurrentFrame(0);
	m_TimeToShoot = 0;
	m_CountBullet = 0;

}

void Tank::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		this->m_Sprite->getAnimationAction()->setIndexStart(0);
		this->m_Sprite->getAnimationAction()->setIndexEnd(1);
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_ALIVE_MOVE:
		m_Sprite->getAnimationAction()->setCurrentFrame(m_Sprite->getAnimationAction()->getCurrentIndex());
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_SHOOTING:
		this->m_Sprite->getAnimationAction()->setIndexStart(0);
		this->m_Sprite->getAnimationAction()->setIndexEnd(23);
		if(m_Sprite->getAnimationAction()->getCurrentIndex() == 23)
			m_Sprite->getAnimationAction()->setCurrentFrame(23);
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_BEFORE_DEATH: 
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	case STATE_JUMP:
		this->m_Sprite->getAnimation()->setCurrentFrame(5);
	default:
		break;
	}
}

void Tank::UpdateCollision(Object* checkingObject)
{
	if (isDead == false)
	{
		if (checkingObject->getID() == eObjectID::BULLET_RAMBO)
		{
			IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
			if (collideDirection != IDDirection::DIR_NONE)
			{
				Bullet* tempBullet = (Bullet*) (checkingObject);
				if (tempBullet->getTypeBullet() == eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO)
				{
					if (m_AttackCounter > 0)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						--m_AttackCounter;
					}
				}
				else if (tempBullet->getTypeBullet() == eIDTypeBullet::RED_BULLET_OF_RAMBO)
				{
					checkingObject->setObjectState(eObjectState::STATE_DEATH);
					if (m_AttackCounter >= 2)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						m_AttackCounter -= 2;
					}
				}
				else if (tempBullet->getTypeBullet() == eIDTypeBullet::FIRE_BULLET_OF_RAMBO)
				{
					if (m_AttackCounter >= 4)
					{
						m_AttackCounter -= 4;
					}
				}

				if (m_AttackCounter <= 0)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
				}
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
		}
	}
}
void Tank::UpdateMovement()
{
		switch (m_ObjectState)
		{
		case STATE_ALIVE_MOVE:
			m_Physic->setVelocityX(-0.5f);
			break;
		case STATE_SHOOTING:
			m_Physic->setVelocityX(0);
			break;
		case STATE_BEFORE_DEATH:
			break;
		case STATE_DEATH:
			break;
		default:
			break;
		}
		m_Physic->UpdateMovement(&m_Position);
	
	
}
void Tank::Update()
{
	m_distance_X = CGlobal::Rambo_X - m_Position.x;
	switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			break;
		case STATE_ALIVE_MOVE:
			if(m_distance_X == -100)
			{
				m_isShoot = true;
				m_ObjectState = eObjectState::STATE_SHOOTING;
			}
			break;
		case STATE_SHOOTING:
			if(m_isShoot == true)
			{
				Shoot();
			}
			if(m_distance_X != -100)
			{
				m_isShoot = false;
				m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
			}
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

void Tank::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != NULL)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void Tank::Release()
{
	m_Sprite = 0;
	sprite_dead->Release();
	sprite_main->Release();
	SAFE_DELETE(sprite_dead);
	SAFE_DELETE(sprite_main);
}
Tank::~Tank()
{
}