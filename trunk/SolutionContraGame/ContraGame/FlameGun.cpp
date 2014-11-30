#include "FlameGun.h"

FlameGun::FlameGun()
{

}

FlameGun::FlameGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	
	
	m_startPosition = _position;
	m_Position.z = 0.4f;
	
}

void FlameGun::Initialize()
{
	m_Position.z = 0.4f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_FLAME_GUN));
}

void FlameGun::UpdateAnimation()
{

}


void FlameGun::UpdateCollision(Object* checkingObject)
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



void FlameGun:: UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
	

}

void FlameGun::Update()
{

}

void FlameGun::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void FlameGun::Release()
{

}

FlameGun::~FlameGun()
{

}