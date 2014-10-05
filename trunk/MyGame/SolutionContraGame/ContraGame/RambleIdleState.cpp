#include "RamboIdleState.h"

RamboIdleState::RamboIdleState()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::BILL_MOVE_1));
}

ObjectState* RamboIdleState::UpdateCollision(Object* hostObject, Object* checkingObject)
{
	return 0;
}
ObjectState* RamboIdleState::UpdateMovement(Object* hostObject)
{
	return 0;
}

RamboIdleState::~RamboIdleState()
{

}