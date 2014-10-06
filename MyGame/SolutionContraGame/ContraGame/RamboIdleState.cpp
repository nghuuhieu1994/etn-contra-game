#include "RamboIdleState.h"

RamboIdleState::RamboIdleState()
{
	m_Sprite = SpriteManager::getInstance()->getSprite(eSpriteID::BILL_MOVE_2);
	m_Physic = new Physic();
}

ObjectState* RamboIdleState::HandleInput(Object* hostObject)
{
	if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
	{
		m_Physic->setPosition( D3DXVECTOR3(m_Physic->getPositionVec3().x + 1, m_Physic->getPositionVec3().y, m_Physic->getPositionVec3().z));
		m_Sprite->setSpriteEffect(eSpriteEffect::None);
	}

	if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
	{
		m_Physic->setPosition( D3DXVECTOR3(m_Physic->getPositionVec3().x - 1, m_Physic->getPositionVec3().y, m_Physic->getPositionVec3().z));
		m_Sprite->setSpriteEffect(eSpriteEffect::Horizontally);
	}
	
	return 0;
}

void RamboIdleState::UpdateAnimation()
{

}

ObjectState* RamboIdleState::UpdateCollision(Object* hostObject, Object* checkingObject)
{
	return 0;
}

ObjectState* RamboIdleState::UpdateMovement(Object* hostObject)
{
	return 0;
}

void RamboIdleState::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, m_Physic->getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), 1.0f);
}

RamboIdleState::~RamboIdleState()
{

}