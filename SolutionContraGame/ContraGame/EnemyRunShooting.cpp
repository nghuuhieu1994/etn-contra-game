#include "EnemyRunShooting.h"
#define VELOC_MOVE_RIGHT 0
#define VELOC_MOVE_LEFT 0
#define VELOC_JUMB		5

EnemyRunShooting::EnemyRunShooting()
{
}

EnemyRunShooting::EnemyRunShooting(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void EnemyRunShooting::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	m_Direction = eDirection::LEFT;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_RUN_SHOOTING));
	m_Sprite = sprite_main;
	isJumb = false;
	isShoot = false;
	isDead = false;
	m_TimeChangeState = 0;
	this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	m_Position.z = 0.4f;
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
		return D3DXVECTOR3(m_Position.x + 8, m_Position.y, 0);
		break;
	case AD_RIGHT:
		return D3DXVECTOR3(m_Position.x - 8, m_Position.y , 0); 
		break;
	default:
		break;	
	}
	return D3DXVECTOR3();
}


void EnemyRunShooting::UpdateAnimation()
{
	if(CGlobal::Rambo_X < m_Position.x)
	{
		m_Direction = eDirection::LEFT;
		m_DirectAttack = eDirectAttack::AD_LEFT;
	}
	else
	{
		m_Direction = eDirection::RIGHT;
		m_DirectAttack = eDirectAttack::AD_RIGHT;
	}

	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE: 
		m_Sprite->getAnimationAction()->setIndexStart(0);
		m_Sprite->getAnimationAction()->setIndexEnd(3);
		m_Sprite->UpdateAnimation(400);
		break;
	case STATE_SHOOTING:
		m_Sprite->getAnimationAction()->setIndexStart(4);
		m_Sprite->getAnimationAction()->setIndexEnd(5);
		m_Sprite->UpdateAnimation(400);
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
	if(m_Direction == eDirection::LEFT)
	{
		m_Sprite->setSpriteEffect(ESpriteEffect::None);
	}

	else
	{
		if(m_Direction == eDirection::RIGHT)
		{
			m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
		}
	}
}
void EnemyRunShooting::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch (checkingObject->getID())
		{
			case eObjectID ::BULLET_RAMBO:
				break;
			case eObjectID::TILE_BASE:
				if (collideDirection == IDDirection::DIR_TOP)
				{
					m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
					this->m_Physic->setVelocityY(0);
				}
				break;
			default:
				break;
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
		//if (isJumb != true)
		//{
		//	if (m_Direction == eDirection::LEFT)
		//	{
		//		m_Physic->setVelocityX(VELOC_MOVE_LEFT);
		//	}
		//	else
		//	{
		//		m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
		//	}
		//}
		//else
		//{
		//	if (m_Direction == eDirection::LEFT)
		//	{
		//		m_Physic->setVelocityX(VELOC_MOVE_LEFT);
		//	}
		//	else
		//	{
		//		m_Physic->setVelocityX(VELOC_MOVE_RIGHT);
		//	}
		//	m_Physic->setVelocityY(VELOC_JUMB);
		//	isJumb = false;
		//}
		break;
	case STATE_BEFORE_DEATH:
		//if (isDead == false)
		//{
		//	if (m_Direction == eDirection::LEFT)
		//	{
		//		m_Physic->setVelocityX(-VELOC_MOVE_LEFT);
		//	}
		//	else
		//	{
		//		m_Physic->setVelocityX(-VELOC_MOVE_RIGHT);
		//	}
		//	m_Physic->setVelocityY(VELOC_JUMB);
		//	isDead = true;
		//}
		break;
	case STATE_EXPLOISION:
		m_Physic->setVelocityX(0);
		m_Physic->setVelocityY(0);
		break;
	case STATE_DEATH:
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
			// do a realthing to detect jumb?
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 10000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_SHOOTING;
				isShoot = true;
			}
			break;
		case STATE_SHOOTING:
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
			if (m_TimeChangeState > 300)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_EXPLOISION;
			}
			break;
		case STATE_EXPLOISION:
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 1000)
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

void EnemyRunShooting::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
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