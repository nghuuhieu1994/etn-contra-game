#include "EnemyRun.h"

EnemyRun::EnemyRun()
{
}

EnemyRun::EnemyRun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position = _position;
}

void EnemyRun::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_RUN));
	m_Sprite = sprite_main;
}

void EnemyRun::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		this->getSprite()->getAnimation()->setIndexStart(0);
		this->getSprite()->getAnimation()->setIndexEnd(2);
		break;
	case STATE_ALIVE_MOVE:
		break;
	case STATE_SHOOTING:
		break;
	case STATE_ENEMY_JUMP:
		this->getSprite()->getAnimation()->setCurrentFrame(1);
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
	m_Sprite->UpdateAnimation(300);
	if(m_Direction == eDirection::LEFT)
		m_Sprite->setSpriteEffect(ESpriteEffect::None);
	else
	{
		if(m_Direction == eDirection::RIGHT)
			m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
	}
}
void EnemyRun::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch (checkingObject->getID())
		{
			case eObjectID ::BULLET_RAMBO:
				if(collideDirection == IDDirection::DIR_TOP)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					break;
				}
				else if(collideDirection == IDDirection::DIR_BOTTOM)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					break;
				}

				else if(collideDirection == IDDirection::DIR_LEFT)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					break;
				}

				else if(collideDirection == IDDirection::DIR_RIGHT)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					break;
				}
				break;

			default:
				break;
		}

	}
}
void EnemyRun::UpdateMovement()
{
	setPositionX(getPositionVec2().x - 1);
}
void EnemyRun::Update()
{
	switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 2000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_ENEMY_JUMP;
			}
			break;
		case STATE_ENEMY_JUMP:
			m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 2000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
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
		case STATE_DEATH:
			this->Release();
			break;
		default:
			break;
		}
}

void EnemyRun::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
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