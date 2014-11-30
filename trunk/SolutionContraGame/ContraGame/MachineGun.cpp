#include "MachineGun.h"

MachineGun::MachineGun()
{

}

MachineGun::MachineGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	
	
	m_startPosition = _position;
	m_Position.z = 0.4f;
	
}

void MachineGun::Initialize()
{
	m_Position.z = 0.4f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MACHINE_GUN));
}

void MachineGun::UpdateAnimation()
{

}


void MachineGun::UpdateCollision(Object* checkingObject)
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



void MachineGun:: UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
	

}

void MachineGun::Update()
{

}

void MachineGun::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void MachineGun::Release()
{

}

MachineGun::~MachineGun()
{

}