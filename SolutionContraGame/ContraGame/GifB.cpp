#include "GifB.h"

GifB::GifB()
{

}

GifB::GifB(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	
	m_Position = _position;
	m_startPosition = _position;
	
}

void GifB::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GIF_F));
}

void GifB::UpdateAnimation()
{

}


void GifB::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch (checkingObject->getID())
		{
			case eObjectID ::RAMBO:
				this->Release();
				break;

			default:
				break;
		}

	}
}



void GifB:: UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);

}

void GifB::Update()
{

}

void GifB::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void GifB::Release()
{

}

GifB::~GifB()
{

}