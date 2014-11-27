#include "RockFlying.h"

RockFlying::RockFlying()
{
}

RockFlying::RockFlying(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void RockFlying::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	m_Direction = eDirection::RIGHT;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ROCK_FLYING));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	m_Position.z = 0.4f;
	//this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	//this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
}

void RockFlying::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
		break;
	case STATE_EXPLOISION:
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void RockFlying::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch (checkingObject->getID())
		{
			case eObjectID ::BULLET_RAMBO:
				break;
			case eObjectID::TILE_BASE:
				break;
			default:
				break;
		}

	}
}
void RockFlying::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
		break;
	case STATE_BEFORE_DEATH:
		break;
	case STATE_EXPLOISION:
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
	m_Physic->UpdateMovement(&m_Position);
}
void RockFlying::Update()
{
	switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			break;
		case STATE_ALIVE_MOVE:
			// do a realthing to detect jumb?

			break;
		case STATE_BEFORE_DEATH:
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

void RockFlying::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void RockFlying::Release()
{
	m_Sprite = 0;
	sprite_dead->Release();
	sprite_main->Release();
}
RockFlying::~RockFlying()
{
}