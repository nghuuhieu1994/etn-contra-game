#include "BoomFlying.h"
BoomFlying::BoomFlying()
{
}

BoomFlying::BoomFlying(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void BoomFlying::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOOM_FLYING));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	//this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	//this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	m_Position.z = 0.4f;
}

void BoomFlying::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
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
void BoomFlying::UpdateCollision(Object* checkingObject)
{
	if( isDead != true )
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

		if(collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
				case eObjectID ::BULLET_RAMBO:
					break;
				default:
					break;
			}
		}
	}
}
void BoomFlying::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_BEFORE_DEATH:
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
	m_Physic->UpdateMovement(&m_Position);
}
void BoomFlying::Update()
{
	switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
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

void BoomFlying::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void BoomFlying::Release()
{
	m_Sprite = 0;
	sprite_dead->Release();
	sprite_main->Release();
}
BoomFlying::~BoomFlying()
{
}