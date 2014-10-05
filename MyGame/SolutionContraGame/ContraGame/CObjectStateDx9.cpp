#include "CObjectStateDx9.h"

ObjectState::ObjectState()
{

}

ObjectState* ObjectState::UpdateCollision(Object* hostObject, Object* checkingObject)
{
	return 0;
}

ObjectState* ObjectState::UpdateMovement(Object* hostObject)
{
	return 0;
}

void ObjectState::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, m_Physic->getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Physic->getPositionVec3().z);
}

ObjectState::~ObjectState()
{

}