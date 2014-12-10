#include "Fire.h"

Fire::Fire()
{
}

Fire::Fire(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void Fire::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_FIRE));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	m_Position.z = 1.0f;
	this->m_Physic->SetMovementRange(this->getBound().top, m_Position.x - 70 , m_Position.x + 70, this->getBound().bottom);
	m_Physic->setVelocityX(0.5f);

}

void Fire::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		m_Sprite->getAnimation()->setIndexStart(0);
		m_Sprite->getAnimation()->setIndexEnd(1);
		m_Sprite->UpdateAnimation(100);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void Fire::UpdateCollision(Object* checkingObject)
{
}

void Fire::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		/*if(m_Direction == eDirection::LEFT)
		{
			m_Physic->setVelocityX(0.3f);
			
		}
		if(m_Direction == eDirection::RIGHT)
		{
			m_Physic->setVelocityX(-0.3f);
			
		}*/
		m_Physic->UpdateMovement(&m_Position);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void Fire::Update()
{
}

void Fire::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void Fire::Release()
{
	m_Sprite = 0;
	sprite_main->Release();
}
Fire::~Fire()
{
}