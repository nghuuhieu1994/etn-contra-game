#include "Stone.h"

Stone::Stone()
{
}

Stone::Stone(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : DynamicObject(_position, _direction, _objectID)
{
}

void Stone::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	m_Direction = eDirection::BOTTOM;
	sprite_exploision = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ROCK_FALLING));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	m_Position.z = 1.0f;
	m_AttackCounter = 8;
	m_isJump = false;
	m_UpdateFlag = false;
	m_TimeToJump = 0;

}

void Stone::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite->getAnimation()->setCurrentFrame(0);
		break;
	case STATE_ALIVE_MOVE:
		m_Sprite->getAnimation()->setIndexStart(0);
		m_Sprite->getAnimation()->setIndexEnd(3);
		m_Sprite->UpdateAnimation(150);
		break;
	case STATE_JUMP:
		m_Sprite->getAnimation()->setIndexStart(0);
		m_Sprite->getAnimation()->setIndexEnd(3);
		m_Sprite->UpdateAnimation(150);
		break;
	case STATE_EXPLOISION:
		m_Sprite = sprite_exploision;
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}

void Stone::UpdateCollision(Object* checkingObject)
{
	if(isDead != true)
	{
		IDDirection collisionDirection = this->m_Collision->CheckCollision(this, checkingObject);
		if(collisionDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			case eObjectID::BULLET_RAMBO:
				{
				Bullet* tempBullet = (Bullet*) (checkingObject);
				if(tempBullet->getTypeBullet() == eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO)
				{
					if(m_AttackCounter > 0)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						--m_AttackCounter;
					}
				}
				if(tempBullet->getTypeBullet() == eIDTypeBullet::FIRE_BULLET_OF_RAMBO)
				{
					if(m_AttackCounter >= 4)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						m_AttackCounter -= 4;;
					}
				}
				if(tempBullet->getTypeBullet() == eIDTypeBullet::LAZER_BULLET_OF_RAMBO)
				{
					if(m_AttackCounter > 0)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						--m_AttackCounter;
					}
				}
				if(tempBullet->getTypeBullet() == eIDTypeBullet::RED_BULLET_OF_RAMBO)
				{
					if(m_AttackCounter > 0)
					{
						SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
						--m_AttackCounter;
					}
				}
				if(m_AttackCounter <= 0)
				{
					m_ObjectState = eObjectState::STATE_EXPLOISION;
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
					checkingObject->setObjectState(eObjectState::STATE_DEATH);
					isDead = true;
				}
			break;
				}
			case eObjectID::TILE_BASE:
				if(collisionDirection == IDDirection::DIR_TOP)
				{
					m_UpdateFlag = !m_UpdateFlag;
					if(m_UpdateFlag == true)
					{
						m_ObjectState = eObjectState::STATE_JUMP;
						m_isJump = true;
					}
					else
					{
						m_Physic->setVelocityY(-7.0f);
						m_Physic->UpdateMovement(&m_Position);
						m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
						m_isJump = false;
					}

				}
				break;
			default:
				break;
			}
		}
	}
}

void Stone::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
		m_Physic->setVelocityY(-1.5f);
		m_Physic->UpdateMovement(&m_Position);
		break;
	case STATE_JUMP:
		if(m_isJump == true)
		{
			m_TimeToJump += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			m_Physic->setVelocityY(1.5f);
			m_Physic->UpdateMovement(&m_Position);
			if(m_TimeToJump > 700)
			{
				m_isJump = false;
				m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
				m_TimeToJump = 0;
			}
		}
		
		break;
		
	default:
		break;
	}
}

void Stone::Update()
{
	switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			break;
		case STATE_ALIVE_MOVE:
			break;
		case STATE_EXPLOISION:
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

void Stone::Render(SPRITEHANDLE _lpSpriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(_lpSpriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
	
}

void Stone::Release()
{
	m_Sprite = 0;
	sprite_exploision->Release();
	sprite_main->Release();
}

Stone::~Stone()
{
}