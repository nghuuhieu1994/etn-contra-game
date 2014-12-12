#include "Boom.h"

Boom::Boom()
{
}

Boom::Boom(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : DynamicObject(_position, _direction, _objectID)
{
}

void Boom::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	m_Direction = eDirection::BOTTOM;
	sprite_exploision = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOOM_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOOM));
	rotate = 10.0f;
	sprite_main->setRotate(rotate);
	m_Sprite = sprite_main;
	m_Position.z = 1.0f;
	m_Physic->setVelocityX(0.3f);
	m_Physic->setVelocityY(0.6f);
	this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	m_TimeChangeState = 0;

}

void Boom::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		m_Sprite->getAnimation()->setCurrentFrame(0);
		rotate += 9.0f;
		m_Sprite->setRotate(rotate);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_exploision;
		m_Sprite->getAnimation()->setIndexStart(0);
		m_Sprite->getAnimation()->setIndexEnd(2);
		m_Sprite->UpdateAnimation(250);
		break;
	default:
		break;
	}
}

void Boom::UpdateCollision(Object* checkingObject)
{
	if(isDead != true)
	{
		IDDirection collisionDirection = this->m_Collision->CheckCollision(this, checkingObject);
		if(collisionDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			case eObjectID::TILE_BASE:
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
					this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					this->getPhysic()->setVelocityY(2.0f);
					this->getPhysic()->setVelocityX(0.0f);
					this->isDead = true;
					break;
			default:
				break;
			}
		}
	}
}

void Boom::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_ALIVE_MOVE:
		m_Physic->UpdateMovement(&m_Position);
		break;
		
	default:
		break;
	}
}

void Boom::Update()
{
	switch (m_ObjectState)
		{
		case STATE_ALIVE_IDLE:
			break;
		case STATE_ALIVE_MOVE:
			break;
		case STATE_BEFORE_DEATH:
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 700)
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

void Boom::Render(SPRITEHANDLE _lpSpriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(_lpSpriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
	
}

void Boom::Release()
{
	m_Sprite = 0;
	sprite_exploision->Release();
	sprite_main->Release();
	SAFE_DELETE(sprite_exploision);
	SAFE_DELETE(sprite_main);
}

Boom::~Boom()
{
}