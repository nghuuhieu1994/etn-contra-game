#include "BridgeStone.h"

#ifndef MOVEMENT_RANGE_BRIDGE_STONE
#define MOVEMENT_RANGE_BRIGDE_STONE 100
#endif
BridgeStone::BridgeStone()
{
}

BridgeStone::BridgeStone(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void BridgeStone::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	m_Direction = eDirection::RIGHT;
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BRIGDE_STONE));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	m_Position.z = 1.0f;
	this->m_Physic->SetMovementRange(this->getBound().top, m_Position.x - MOVEMENT_RANGE_BRIGDE_STONE, m_Position.x + MOVEMENT_RANGE_BRIGDE_STONE, this->getBound().bottom);
	m_Physic->setVelocityX(0.3f);
}

void BridgeStone::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void BridgeStone::UpdateCollision(Object* checkingObject)
{
}

void BridgeStone::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		m_Physic->UpdateMovement(&m_Position);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void BridgeStone::Update()
{
}

void BridgeStone::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void BridgeStone::Release()
{
	m_Sprite = 0;
	sprite_main->Release();
	SAFE_DELETE(sprite_main);
}
BridgeStone::~BridgeStone()
{
}