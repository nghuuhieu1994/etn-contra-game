#include "BridgeTile.h"

BridgeTile::BridgeTile(){}

BridgeTile::BridgeTile(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{

}
BridgeTile::~BridgeTile(){}

void BridgeTile::Initialize()
{
}
void BridgeTile::UpdateAnimation()
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
	};
}
void BridgeTile::UpdateCollision(Object* checkingObject)
{
	if (!isDead)
	{

	}
}
void BridgeTile::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_BEFORE_DEATH:
		break;
	case STATE_DEATH:
		this->Release();
		break;
	}
}
void BridgeTile::Render(SPRITEHANDLE spriteHandle)
{
	if (!m_Sprite)
	{
		m_Sprite->Render(spriteHandle, 
										getPositionVec2(), 
										m_Sprite->getSpriteEffect(), 
										m_Sprite->getRotate(), 
										m_Sprite->getScale(), 
										m_Position.z);
	}
}
void BridgeTile::Release()
{
	m_BridgeSprite->Release();
	m_DeadSprite->Release();
	m_Sprite = 0;
}
