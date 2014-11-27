#include "Bridge.h"

Bridge::Bridge()
{
}

Bridge::Bridge(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void Bridge::Initialize()
{
	m_HeadTile = new BridgeTile(D3DXVECTOR3(m_Position.x - 62 / 2 - 64, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_HEAD);
	m_HeadTile->Initialize();
	m_TailTile = new BridgeTile(D3DXVECTOR3(m_Position.x + 64 + 62 / 2, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_TAIL);
	m_TailTile->Initialize();
	m_BodyTile[0] = new BridgeTile(D3DXVECTOR3(m_Position.x - 62 / 2, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_BODY);
	m_BodyTile[0]->Initialize();
	m_BodyTile[1] = new BridgeTile(D3DXVECTOR3(m_Position.x + 62 / 2, m_Position.y, m_Position.z), eDirection::LEFT, eObjectID::BRIDGE_BODY);
	m_BodyTile[1]->Initialize();
	m_HeadBreak = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_HEAD_BREAK);
	m_TailBreak = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_TAIL_BREAK);
}

void Bridge::UpdateAnimation()
{
	m_HeadTile->UpdateAnimation();
	m_BodyTile[0]->UpdateAnimation();
	m_BodyTile[1]->UpdateAnimation();
	m_TailTile->UpdateAnimation();
}


void Bridge::UpdateCollision(Object* checkingObject)
{
	m_HeadTile->UpdateCollision(checkingObject);
	m_BodyTile[0]->UpdateCollision(checkingObject);
	m_BodyTile[1]->UpdateCollision(checkingObject);
	m_TailTile->UpdateCollision(checkingObject);
}

void Bridge:: UpdateMovement()
{
}

void Bridge::Update()
{
	_distanceX = m_Position.x - CGlobal::Rambo_X;
	if (_distanceX <= 200)
	{
		isDead = true;
	}
	if (isDead == true)
	{
		if (m_HeadTile->isDead == false)
		{
			m_HeadTile->setObjectState(STATE_BEFORE_DEATH);
		}
		if (m_HeadTile->getObjectState() == STATE_DEATH)
		{
			if (m_BodyTile[0]->isDead != true)
			{
				m_BodyTile[0]->setObjectState(STATE_BEFORE_DEATH);
			}
		}
		if (m_BodyTile[0]->getObjectState() == STATE_DEATH)
		{
			if (m_BodyTile[1]->isDead != true)
			{
				m_BodyTile[1]->setObjectState(STATE_BEFORE_DEATH);
			}
		}
		if (m_BodyTile[1]->getObjectState() == STATE_DEATH)
		{
			if (m_TailTile->isDead != true)
			{
				m_TailTile->setObjectState(STATE_BEFORE_DEATH);
			}
		}
	}
	m_HeadTile->Update();
	m_BodyTile[0]->Update();
	m_BodyTile[1]->Update();
	m_TailTile->Update();
}

void Bridge::Render(SPRITEHANDLE spriteHandle)
{
	m_HeadBreak->Render(spriteHandle, m_HeadTile->getPositionVec2(), ESpriteEffect::None, 0.0f, 1.0f, 1);
	m_TailBreak->Render(spriteHandle, m_TailTile->getPositionVec2() , ESpriteEffect::None, 0.0f, 1.0f, 1);
	m_TailTile->Render(spriteHandle);
	m_BodyTile[1]->Render(spriteHandle);
	m_BodyTile[0]->Render(spriteHandle);
	m_HeadTile->Render(spriteHandle);
}

void Bridge::Release()
{
}

Bridge::~Bridge()
{
}