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
	if (m_CountBullet < 4)
	{
		if (m_TimeToShoot >= 500)
		{
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPosition(), D3DXVECTOR2(-1.0f, 0.0f), GetAnpla());
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

float Tank::GetAnpla()
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
		return 0.0f;
		break;
	case 2:
	case 3:
	case 8:
	case 9:
	case 14:
	case 15:
	case 20:
	case 21:
		return 0.57f;
		break;
	case 4:
	case 5:
	case 10:
	case 11:
	case 16:
	case 17:
	case 22:
	case 24:
		return 1.19f;
		break;
	default:
		break;
	}
	return 0.0f;
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
		return D3DXVECTOR3(m_Position.x - 100, m_Position.y + 37, 1);
		break;
	case 2:
	case 3:
	case 8:
	case 9:
	case 14:
	case 15:
	case 20:
	case 21:
		return D3DXVECTOR3(m_Position.x - 87, m_Position.y + 18, 1);
		break;
	case 4:
	case 5:
	case 10:
	case 11:
	case 16:
	case 17:
	case 22:
	case 24:
		return D3DXVECTOR3(m_Position.x - 77, m_Position.y + 7, 1);
		break;
	default:
		break;
	}
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Tank::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_TANK));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	m_Physic->setAccelerateY(-0.01f);
	m_Position.z = 1.0f;
	m_Direction = eDirection::LEFT;
	m_AttackCounter = 80;
	m_Sprite->getAnimationAction()->setCurrentFrame(0);
	m_TimeToShoot = 0;
	m_CountBullet = 0;
	m_isShoot = false;

}

void Tank::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		m_Sprite->getAnimationAction()->setCurrentFrame(m_Sprite->getAnimationAction()->getCurrentIndex());
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_SHOOTING:
		m_isShoot = true;
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		//if(this->m_Sprite != 0)
		//	this->Release();
		break;	
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
#pragma region BulletRambo
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
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						m_AttackCounter -= 4;
					}
				}
				else if(tempBullet->getTypeBullet() == eIDTypeBullet::LAZER_BULLET_OF_RAMBO)
				{
					// L Bullet
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
					m_AttackCounter -= 5;
				}

				if(m_AttackCounter >= 65 && m_AttackCounter <= 80)
				{
					m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
					//m_isShoot = true;
					this->m_Sprite->getAnimationAction()->setIndexStart(0);
					this->m_Sprite->getAnimationAction()->setIndexEnd(5);
					m_Sprite->UpdateAnimation(250);

				}
				else if(m_AttackCounter >=49  && m_AttackCounter < 65)
				{
					m_ObjectState = eObjectState::STATE_SHOOTING;
					m_isShoot = true;
					this->m_Sprite->getAnimationAction()->setIndexStart(6);
					this->m_Sprite->getAnimationAction()->setIndexEnd(11);
					m_Sprite->UpdateAnimation(250);
				}
				else if(m_AttackCounter >= 33 && m_AttackCounter < 49)
				{
					m_ObjectState = eObjectState::STATE_SHOOTING;
					m_isShoot = true;
					this->m_Sprite->getAnimationAction()->setIndexStart(12);
					this->m_Sprite->getAnimationAction()->setIndexEnd(17);
					m_Sprite->UpdateAnimation(250);
				}
				else if(m_AttackCounter >= 1 && m_AttackCounter < 33)
				{
					m_ObjectState = eObjectState::STATE_SHOOTING;
					m_isShoot = true;
					this->m_Sprite->getAnimationAction()->setIndexStart(18);
					this->m_Sprite->getAnimationAction()->setIndexEnd(23);
					m_Sprite->UpdateAnimation(250);
				}

				
				if (m_AttackCounter <= 0)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					m_TimeChangeState = 0;
					isDead = true;
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
				}
				checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
#pragma endregion
		}

		if (checkingObject->getID() == eObjectID::TILE_BASE)
		{
			IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
			if (collideDirection == IDDirection::DIR_TOP)
			{
				this->m_Physic->setVelocityY(0);
			}
		}
	}
}
void Tank::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		m_Physic->setVelocityX(-0.2f);
		break;
	case STATE_SHOOTING:
		m_Physic->setVelocityX(0.0f);
		break;
	default:
		break;
	}
	m_Physic->UpdateMovement(&m_Position);
}
void Tank::Update()
{
	m_distance_X = (int)(CGlobal::Rambo_X - m_Position.x);
	switch (m_ObjectState)
		{
		case STATE_ALIVE_MOVE:
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 2000)
			{
				m_TimeChangeState = 0;
				m_isShoot = true;
				m_ObjectState= eObjectState::STATE_SHOOTING;
			}
			break;
		case STATE_SHOOTING:
			if(m_isShoot == true)
			{
				m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if (m_TimeChangeState > 3000)
				{
					m_TimeToShoot = 1000;
					Shoot();
					m_TimeChangeState = 0;
					m_ObjectState= eObjectState::STATE_ALIVE_MOVE;
				}
			}
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 3000)
			{
				m_TimeChangeState = 0;
				m_isShoot = false;
				m_ObjectState= eObjectState::STATE_ALIVE_MOVE;
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
			if(this->m_Sprite != 0)
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