#include "Gun_1.h"

Gun_1::Gun_1()
{

}

Gun_1::Gun_1(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: Object(_position, _direction, _objectID)
{
}

void Gun_1::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GUN_1));
}

void Gun_1::UpdateAnimation()
{
	//delete m_Sprite;
	//m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BIG_FAT_GUN));
	m_Sprite->UpdateAnimation(300);		
	
}


void Gun_1::UpdateCollision(Object* checkingObject)
{}

void Gun_1:: UpdateMovement()
{}

void Gun_1::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, m_Physic->getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Physic->getPositionVec3().z);
}


void Gun_1::Release()
{

}

Gun_1::~Gun_1()
{

}