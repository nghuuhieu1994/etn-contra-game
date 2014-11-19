#include "Bridge.h"

Bridge::Bridge()
{

}

Bridge::Bridge(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position = _position;
	
}

void Bridge::Initialize()
{
	//m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GIF_BULLET_MOVING));
}

void Bridge::UpdateAnimation()
{

}


void Bridge::UpdateCollision(Object* checkingObject)
{
	
}

void Bridge:: UpdateMovement()
{
	
}

void Bridge::Update()
{

}

void Bridge::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void Bridge::Release()
{

}

Bridge::~Bridge()
{

}