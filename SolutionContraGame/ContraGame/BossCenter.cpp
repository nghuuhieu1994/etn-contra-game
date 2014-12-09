#include "BossCenter.h"



BossCenter::BossCenter()
{

}

BossCenter::BossCenter(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
}

void BossCenter::Initialize()
{
	m_AttackCounter = 1;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_CENTER);
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
	m_Position.z = 1.0f;
}

void BossCenter::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: 
		m_Sprite->UpdateAnimation(800);
		break;
	case STATE_BEFORE_DEATH:
		if(isDead == false)
		{
			isDead = true;
			m_Sprite = sprite_dead;
		}
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}	
}


void BossCenter::UpdateCollision(Object* checkingObject)
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
					//this->isDead = true;
				}
				//checkingObject->setObjectState(eObjectState::STATE_DEATH);
			}
		}
	}
}

void BossCenter:: UpdateMovement()
{}
void BossCenter::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_BEFORE_DEATH:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
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
void BossCenter::Render(SPRITEHANDLE spriteHandle)
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


void BossCenter::Release()
{
	m_Sprite = 0;
	if (sprite_alive)
	{
		sprite_alive->Release();
	}
	SAFE_DELETE(sprite_alive);
	if (sprite_dead)
	{
		sprite_dead->Release();
	}
	SAFE_DELETE(sprite_dead);
}

BossCenter::~BossCenter()
{

}