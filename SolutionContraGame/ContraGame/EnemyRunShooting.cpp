#include "EnemyRunShooting.h"

#define VELOC_MOVE_RIGHT 1.0f
#define VELOC_MOVE_LEFT -1.0f
#define VELOC_JUMB		0.8f

EnemyRunShooting::EnemyRunShooting()
{
}

EnemyRunShooting::EnemyRunShooting(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyRunShooting::Initialize()
{
	m_ObjectState = eObjectState::STATE_JUMP;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_RUN_SHOOTING));
	m_Sprite = sprite_main;
	isJumb = false;
	m_TimeChangeState = 0;
	this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	m_Position.z = 1.0f;
	m_Direction = eDirection::LEFT;
	this->isDead = false;
}

void EnemyRunShooting::Shoot()
{
	switch (m_DirectAttack)
	{
	case AD_LEFT:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(-3.5f, 0.0f), 0);
		break;
	case AD_RIGHT:
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_ENEMY, GetStartPositionOfBullet(), D3DXVECTOR2(2.0f, 0.0f), 0);
		break;
	default:
		break;	
	}
}

D3DXVECTOR3  EnemyRunShooting::GetStartPositionOfBullet()
{
	switch(m_DirectAttack)
	{
	case AD_LEFT:
		return D3DXVECTOR3(m_Position.x + 8, m_Position.y + 15, 0);
		break;
	case AD_RIGHT:
		return D3DXVECTOR3(m_Position.x - 8, m_Position.y + 15, 0); 
		break;
	default:
		break;	
	}
	return D3DXVECTOR3();
}


void EnemyRunShooting::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		this->m_Sprite->getAnimationAction()->setCurrentFrame(3);
		break;
	case STATE_ALIVE_MOVE:
		this->m_Sprite->getAnimationAction()->setIndexStart(0);
		this->m_Sprite->getAnimationAction()->setIndexEnd(2);
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_BEFORE_DEATH: 
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	case STATE_JUMP:
		this->m_Sprite->getAnimation()->setCurrentFrame(1);
		break;
	case STATE_SHOOTING:
		this->m_Sprite->getAnimation()->setCurrentFrame(5);
		break;
	default:
		break;
	}
}
void EnemyRunShooting::UpdateCollision(Object* checkingObject)
{
	if( isDead != true )
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

		if(collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
				case eObjectID ::BULLET_RAMBO:
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
					this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					this->getPhysic()->setVelocityY(2.0f);
					this->getPhysic()->setVelocityX(0.0f);
					this->isDead = true;
					break;
				case eObjectID::BRIDGE:
				case eObjectID::TILE_BASE:
					if (collideDirection == IDDirection::DIR_TOP)
						{
							if(m_ObjectState == eObjectState::STATE_JUMP)
							{
								m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
								this->isJumb = false;
							}
							this->m_Position.y += this->m_Collision->m_MoveY;
							this->m_Physic->setVelocityY(0.0f);
						}
					else
					{
						m_ObjectState = eObjectState::STATE_JUMP;
						this->isJumb = true;
					}
					break;
				case eObjectID::VIRTUAL_OBJECT_JUMP:
						if((collideDirection == IDDirection::DIR_LEFT || collideDirection == IDDirection::DIR_RIGHT) && m_ObjectState != eObjectState::STATE_JUMP)
						{
							this->isJumb = true;
							m_ObjectState = eObjectState::STATE_JUMP;
							m_Physic->setVelocityY(VELOC_JUMB);
						}	
					break;
				default:
					break;
			}
		}
	}
}
void EnemyRunShooting::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
			if (m_Direction == eDirection::LEFT)
			{
				m_Physic->setVelocityX(VELOC_MOVE_LEFT);
			}
			else
			{
				m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
			}
		break;
	case STATE_JUMP:
			if (m_Direction == eDirection::LEFT)
			{
				m_Physic->setVelocityX(VELOC_MOVE_LEFT);
			}
			else
			{
				m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
			}
			if(isJumb == true)
			{
				isJumb = false;
			}
		break;
	case STATE_BEFORE_DEATH:
		if (isDead == false)
		{
			if (m_Direction == eDirection::LEFT)
			{
				m_Physic->setVelocityX(-VELOC_MOVE_LEFT);
			}
			else
			{
				m_Physic->setVelocityX(-VELOC_MOVE_RIGHT);
			}
			setPositionY(getPositionVec2().y + 2);
			m_Physic->setVelocityY(VELOC_JUMB);
			m_Physic->setAccelerate(D3DXVECTOR2(0, 0));
			isDead = true;
		}
		break;
	case STATE_DEATH:
		break;
	case STATE_SHOOTING:
		if(isDead == false)
		{
			m_Physic->setVelocityX(0.0f);
		}
		break;
	default:
		break;
	}

	m_Physic->UpdateMovement(&m_Position);
}
void EnemyRunShooting::Update()
{
	switch (m_ObjectState)
		{
		case STATE_ALIVE_MOVE:
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 2000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_SHOOTING;
				isShoot = true;
			}
			break;
		case STATE_SHOOTING:
			if(m_Direction == eDirection::LEFT)
				this->m_DirectAttack = eDirectAttack::AD_LEFT;
			else
				this->m_DirectAttack = eDirectAttack::AD_RIGHT;
			if(isShoot == true)
			{
				Shoot();
				isShoot = false;
			}
			m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 3000)
			{
				m_TimeChangeState = 0;
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
			if(this->m_Sprite != 0)
			this->Release();
			break;
		default:
			break;
		}
}

void EnemyRunShooting::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		if(m_Direction == eDirection::RIGHT)
		{
			this->getSprite()->setSpriteEffect(ESpriteEffect::None);
		}
		else
		{
			this->getSprite()->setSpriteEffect(ESpriteEffect::Horizontally);
		}
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void EnemyRunShooting::Release()
{
	m_Sprite = 0;
	sprite_dead->Release();
	sprite_main->Release();
	SAFE_DELETE(sprite_dead);
	SAFE_DELETE(sprite_main);
}
EnemyRunShooting::~EnemyRunShooting()
{
}