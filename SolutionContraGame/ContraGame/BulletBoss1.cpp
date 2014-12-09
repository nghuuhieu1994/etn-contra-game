#include "BulletBoss1.h"


BulletBoss1::BulletBoss1()
{

}

BulletBoss1::BulletBoss1(D3DXVECTOR3 _position, eDirection _direction, eObjectID _id) : Bullet(_position, _direction, _id)
{

}

void BulletBoss1::Initialize()
{
	sprite_alive_move =  new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	this->m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	this->m_Sprite = sprite_alive_move;
	this->m_Sprite->setScale(0.7f);
	this->m_Position.z = 1.0f;
	this->m_Physic->setVelocityX(2.0f);
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
	this->m_TypeBullet = eIDTypeBullet::BULLET_OF_BOSS1;
	this->m_DirectAttack = eDirectAttack::AD_LEFT;
	this->m_factor = 0;
	this->isDead = false;
}

void BulletBoss1::UpdateMovement()
{
	this->getPhysic()->UpdateMovement(&this->m_Position);
}

void BulletBoss1::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		this->getSprite()->setScale(1.0f);
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

void BulletBoss1::Update()
{
	switch (m_ObjectState)
		{
		case STATE_ALIVE_MOVE:
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
			this->Initialize();
			break;
		default:
			break;
		}

}

void BulletBoss1::UpdateCollision(Object* checkingObject)
{
	if(this->isDead == false)
	{
		if(checkingObject->getID() == eObjectID::TILE_BASE || checkingObject->getID() == eObjectID::RAMBO)
		{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

			if(collideDirection != IDDirection::DIR_NONE)
			{
				switch (checkingObject->getID())
				{
					case eObjectID::TILE_BASE:
						if (collideDirection == IDDirection::DIR_TOP && CGlobal::Rambo_Y >= checkingObject->getPositionVec2().y)
							{
								m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
								this->m_Position.y += this->m_Collision->m_MoveY;
								this->isDead = true;
								this->m_Physic->setVelocityX(0.0f);
								this->m_Physic->setVelocityY(0.0f);
								this->m_Physic->setAccelerateX(0.0f);
								this->m_Physic->setAccelerateY(0.0f);
							}
						break;
					case eObjectID::RAMBO:
							//m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
							//this->m_Position.y += this->m_Collision->m_MoveY;
							//this->m_Physic->setVelocityY(0.0f);
							break;
					default:
						break;
				}
			}
		}
	}
}

BulletBoss1::~BulletBoss1()
{

}
