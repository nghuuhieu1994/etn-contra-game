#include "Bullet.h"


Bullet::Bullet()
{

}

Bullet::Bullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	
	this->m_Direction = _direction;
	this->m_eObjectID = _objectID;
	this->m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
}

void Bullet::reset()
{
	this->m_factor = 0;
	//this->getPhysic()->setVelocityX(2.0f);
	this->getPhysic()->setVelocityX(0.0f);
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
	//this->m_Sprite->Release();
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
		reset();
	}
}

void Bullet::UpdateAnimation()
{
	this->m_Sprite->UpdateAnimation(200);
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
