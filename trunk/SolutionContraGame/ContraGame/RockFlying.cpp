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
	m_Sprite  = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ROCK_FLYING));
	m_TimeChangeState = 0;
	m_Position.z = 0.4f;
	this->m_Physic->setVelocity(D3DXVECTOR2(0, 0));
	//this->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
}

void RockFlying::UpdateAnimation()
{
	m_Sprite->getAnimationAction()->setCurrentFrame(0);
}
void RockFlying::UpdateCollision(Object* checkingObject)
{
}

void RockFlying::UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
	m_Physic->setVelocityX(0.5f);
}

void RockFlying::Update()
{
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
}
RockFlying::~RockFlying()
{
}