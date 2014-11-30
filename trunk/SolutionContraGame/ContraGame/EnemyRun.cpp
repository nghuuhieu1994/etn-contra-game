#include "EnemyRun.h"
#define VELOC_MOVE_RIGHT 1.0f
#define VELOC_MOVE_LEFT -1.0f
#define VELOC_JUMB	0.5f

EnemyRun::EnemyRun()
{
}

EnemyRun::EnemyRun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 1.0f;
}

void EnemyRun::Initialize()
{
	m_ObjectState = eObjectState::STATE_JUMP;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_RUN));
	m_Sprite = sprite_main;
	isJumb = false;
	m_TimeChangeState = 0;
	this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	m_Position.z = 1.0f;
	m_Direction = eDirection::LEFT;
}

void EnemyRun::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		this->m_Sprite->getAnimationAction()->setCurrentFrame(3);
		break;
	case STATE_ALIVE_MOVE:
		this->m_Sprite->getAnimationAction()->setIndexStart(0);
		this->m_Sprite->getAnimationAction()->setIndexEnd(5);
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

bool EnemyRun::CanCollisionWithVirtualObject(VirtualObject* virtualObject)
{
	if((this->m_Position.y - virtualObject->getPositionVec3().y > this->getSprite()->getAnimation()->getFrameSize().y))
	{
		return true;
	}
	return false;
}

void EnemyRun::UpdateCollision(Object* checkingObject)
{
	if( isDead != true )
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

		if(collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
				case eObjectID ::BULLET_RAMBO:
					checkingObject->setObjectState(eObjectState::STATE_DEATH);
					this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					this->isDead = true;
					break;
				case eObjectID::TILE_BASE:
					if (collideDirection == IDDirection::DIR_TOP)
						{
							m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
							this->isJumb = false;
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
void EnemyRun::UpdateMovement()
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
	default:
		break;
	}

	m_Physic->UpdateMovement(&m_Position);
}
void EnemyRun::Update()
{
	switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			break;
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
			break;
		default:
			break;
		}

}

void EnemyRun::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != NULL)
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

void EnemyRun::Release()
{
	m_Sprite = 0;
	sprite_dead->Release();
	sprite_main->Release();
}
EnemyRun::~EnemyRun()
{
}