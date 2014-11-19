#include "RockFalling.h"


RockFalling::RockFalling()
{
}

RockFalling::RockFalling(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void RockFalling::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ROCK_FALLING));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	//this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	//this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
}

void RockFalling::UpdateAnimation()
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
void RockFalling::UpdateCollision(Object* checkingObject)
{
	
}
void RockFalling::UpdateMovement()
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
void RockFalling::Update()
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

void RockFalling::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void RockFalling::Release()
{
	m_Sprite = 0;
	sprite_dead->Release();
	sprite_main->Release();
}
RockFalling::~RockFalling()
{
}