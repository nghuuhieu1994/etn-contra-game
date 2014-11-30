#include "WeaponCapsule.h"

WeaponCapsule::WeaponCapsule()
{

}

WeaponCapsule::WeaponCapsule(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_startPosition = _position;
	m_Position.z = 0.4f;
}

void WeaponCapsule::Initialize()
{
	m_Position.z = 0.4f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_WEAPON_CAPSULE));
}

void WeaponCapsule::UpdateAnimation()
{

}


void WeaponCapsule::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch (checkingObject->getID())
		{
			case eObjectID ::BULLET_RAMBO:
				if(collideDirection == IDDirection::DIR_TOP)
				{
					break;
				}
				else if(collideDirection == IDDirection::DIR_BOTTOM)
				{
					
					break;
				}

				else if(collideDirection == IDDirection::DIR_LEFT)
				{
					
					break;
				}

				else if(collideDirection == IDDirection::DIR_RIGHT)
				{
					
					break;
				}
				break;

			default:
				break;
		}

	}
}

float WeaponCapsule::Moving()
{
	return (float)((sin(m_Position.x * 3.14/80.0 ) * 100 + m_startPosition.y) - m_Position.y);
}

void WeaponCapsule:: UpdateMovement()
{
	//
	//m_Physic->setVelocity(D3DXVECTOR2(1.5f, m_Physic->getVelocity().y));
	m_Physic->UpdateMovement(&m_Position);
	m_Physic->setVelocityY((sin(m_Position.x * 3.14/80.0 ) * 100 + m_startPosition.y) - m_Position.y);
	m_Physic->setVelocityX(1.5f);
	
	//Sin(m_Position);
}

void WeaponCapsule::Update()
{

}

void WeaponCapsule::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void WeaponCapsule::Release()
{

}

WeaponCapsule::~WeaponCapsule()
{

}