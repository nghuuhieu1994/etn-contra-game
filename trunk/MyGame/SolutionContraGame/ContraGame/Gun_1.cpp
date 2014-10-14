#include "Gun_1.h"

Gun_1::Gun_1()
{

}

Gun_1::Gun_1(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: Object(_position, _direction, _objectID)
{
	m_Physic = new Physic();
	//m_Physic->setPosition(_position);
	m_Position = _position;
}

void Gun_1::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GUN_1));
}

void Gun_1::UpdateAnimation()
{
	m_Sprite->UpdateAnimation(300);	
	
}


void Gun_1::UpdateCollision(Object* checkingObject)
{}

void Gun_1:: UpdateMovement()
{}
void Gun_1::Update()
{}
void Gun_1::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}


void Gun_1::Release()
{

}

Gun_1::~Gun_1()
{

}