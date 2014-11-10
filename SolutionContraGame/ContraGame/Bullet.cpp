#include "Bullet.h"


Bullet::Bullet()
{

}

Bullet::Bullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	this->m_Position = _position;
	this->m_Direction = _direction;
	this->m_eObjectID = _objectID;
	this->m_Position.z = 1.0f;
	this->m_Physic->setVelocityX(2.0f);
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
	this->m_TypeBullet = eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO;
	this->m_DirectAttack = eDirectAttack::AD_TOP;
}

void Bullet::Initialize()
{
	this->m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_DEFAULT_BULLET_RAMBO));
}

void Bullet::reset()
{
	this->getPhysic()->setVelocityX(2.0f);
	this->getPhysic()->setVelocityY(0.0f);
}

void Bullet::ResetLivingTime()
{
	this->m_ObjectState = eObjectState::STATE_ALIVE_MOVE; 
	m_livingTime = 0;
}

void Bullet::Release()
{
	this->m_Sprite = 0;
}

void Bullet::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, this->getPositionVec2(), this->m_Sprite->getSpriteEffect(), this->m_Sprite->getRotate(), 
			this->m_Sprite->getScale(), this->getPositionVec3().z);
	}
}

void Bullet::Update()
{
	m_livingTime += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (m_livingTime > 4000)
	{
		m_ObjectState = eObjectState::STATE_DEATH;
	}
}

void Bullet::UpdateAnimation()
{
	switch(this->m_ObjectState)
	{
	case eObjectState::STATE_ALIVE_MOVE:
		this->m_Sprite->getAnimation()->setIndexStart(0);
		this->m_Sprite->getAnimation()->setIndexEnd(0);
		break;
	case eObjectState::STATE_DEATH:
		break;
	default:
		break;
	}

	this->m_Sprite->UpdateAnimation(300);
}

void Bullet::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch(collideDirection)
		{
		case IDDirection::DIR_TOP:
			break;
		case IDDirection::DIR_BOTTOM:
			break;
		case IDDirection::DIR_LEFT:
			break;
		case IDDirection::DIR_RIGHT:
			break;
		default:
			break;
		}
	}
}

void Bullet::UpdateMovement()
{
	// Implement movement equation
	this->m_Physic->UpdateMovement(&this->m_Position);
}

Bullet::~Bullet()
{

}
