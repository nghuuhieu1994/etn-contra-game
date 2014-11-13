#include "GifS.h"

GifS::GifS()
{

}

GifS::GifS(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	
	m_Position = _position;
	m_startPosition = _position;
	
}

void GifS::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GIF_S));
}

void GifS::UpdateAnimation()
{

}


void GifS::UpdateCollision(Object* checkingObject)
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



void GifS:: UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
	

}

void GifS::Update()
{

}

void GifS::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void GifS::Release()
{

}

GifS::~GifS()
{

}