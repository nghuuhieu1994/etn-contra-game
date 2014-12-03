#include "MagicRock.h"

MagicRock::MagicRock()
{
}

MagicRock::MagicRock(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void MagicRock::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_MOVE;
	m_Direction = eDirection::RIGHT;
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MAGIC_ROCK));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	m_Position.z = 0.4f;
	this->m_Physic->SetMovementRange(this->getBound().top, m_Position.x - 50, m_Position.x + 50, this->getBound().bottom);
	m_Physic->setVelocityX(0.3f);
}

void MagicRock::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		m_Sprite->getAnimation()->setCurrentFrame(0);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void MagicRock::UpdateCollision(Object* checkingObject)
{
}

void MagicRock::UpdateMovement()
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
void MagicRock::Update()
{
}

void MagicRock::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void MagicRock::Release()
{
	m_Sprite = 0;
	sprite_main->Release();
}
MagicRock::~MagicRock()
{
}