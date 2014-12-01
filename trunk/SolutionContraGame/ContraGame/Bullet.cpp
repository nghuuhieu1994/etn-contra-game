#include "Bullet.h"


Bullet::Bullet()
{
	m_Position.z = 1.0f;
}

Bullet::Bullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	
	this->m_Direction = _direction;
	this->m_eObjectID = _objectID;
	this->m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	this->m_Position.z = 1.0f;
}

void Bullet::reset()
{
	this->m_Position.z = 1.0f;
	this->m_factor = 0;
	this->getPhysic()->setVelocityX(2.0f);
	//this->getPhysic()->setVelocityX(0.0f);
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
	if (!Intersect(Camera::getInstance()->getBound(), this->getBound()))
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
	//if(checkingObject->getObjectState() != eObjectState::STATE_BEFORE_DEATH && checkingObject->getObjectState() != eObjectState::STATE_DEATH)
	//{
	//	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	//	if(collideDirection != IDDirection::DIR_NONE)
	//	{
	//		if(checkingObject->getTypeObject() != ETypeObject::VIRTUAL_OBJECT && checkingObject->getTypeObject() != ETypeObject::TILE_MAP)
	//		{
	//			if(this->getID() == eObjectID::BULLET_RAMBO)
	//			{
	//				if(checkingObject->getID() != eObjectID::RAMBO && checkingObject->getID() != eObjectID::SNIPER_HIDING)
	//				{
	//					//this->m_ObjectState = eObjectState::STATE_DEATH;
	//				}
	//				else if(checkingObject->getID() == eObjectID::SNIPER_HIDING)
	//				{
	//					if(checkingObject->getObjectState() != eObjectState::STATE_ALIVE_IDLE)
	//					{
	//						//this->m_ObjectState = eObjectState::STATE_DEATH;
	//					}
	//				}
	//			}
	//			else if(this->getID() == eObjectID::BULLET_ENEMY)
	//			{
	//				if(checkingObject->getID() == eObjectID::RAMBO)
	//				{
	//					//this->m_ObjectState = eObjectState::STATE_DEATH;
	//				}
	//			}
	//		}
	//	}
	//}
}

void Bullet::UpdateMovement()
{
	this->m_Physic->UpdateMovement(&this->m_Position);
}

Bullet::~Bullet()
{

}
