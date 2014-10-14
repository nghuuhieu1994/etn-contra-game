#include "Flyer_Sin.h"

Flyer_Sin::Flyer_Sin()
{

}

Flyer_Sin::Flyer_Sin(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: Object(_position, _direction, _objectID)
{
	m_Physic = new Physic();
	//m_Physic->setPosition(_position);
	m_Position = _position;
	m_startPosition = _position;
}

void Flyer_Sin::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_FLYER_SIN));
}

void Flyer_Sin::UpdateAnimation()
{
	m_Sprite->UpdateAnimation(400);		
	
}


void Flyer_Sin::UpdateCollision(Object* checkingObject)
{}

void Flyer_Sin::Sin(D3DXVECTOR3& a)
{
	a.y = sin(a.x * 3.14 / 180.0) * 50 + m_startPosition.y;
	a.x += 1.0;
}

void Flyer_Sin:: UpdateMovement()
{
	//m_Physic->setVelocity(D3DXVECTOR2(1.5f, m_Physic->getVelocity().y));
	//this->m_Physic->UpdateMovement(&m_Position);
	Sin(m_Position);
}
void Flyer_Sin::Update()
{
}
void Flyer_Sin::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}


void Flyer_Sin::Release()
{

}

Flyer_Sin::~Flyer_Sin()
{

}