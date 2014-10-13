#include "Flyer_Sin.h"

Flyer_Sin::Flyer_Sin()
{

}

Flyer_Sin::Flyer_Sin(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: Object(_position, _direction, _objectID)
{
	m_Physic = new Physic();
	m_Physic->setPosition(_position);
}

void Flyer_Sin::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_FLYER_SIN));
}

void Flyer_Sin::UpdateAnimation()
{
	//delete m_Sprite;
	//m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BIG_FAT_GUN));
	m_Sprite->UpdateAnimation(300);		
	
}


void Flyer_Sin::UpdateCollision(Object* checkingObject)
{}

void Flyer_Sin:: UpdateMovement()
{}

void Flyer_Sin::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, m_Physic->getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Physic->getPositionVec3().z);
}


void Flyer_Sin::Release()
{

}

Flyer_Sin::~Flyer_Sin()
{

}