#include "GifBulletSinStraight.h"

GifBulletSinStraight::GifBulletSinStraight()
{

}

GifBulletSinStraight::GifBulletSinStraight(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	
	m_startPosition = _position;
	
}

void GifBulletSinStraight::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GIF_BULLET_MOVING));
}

void GifBulletSinStraight::UpdateAnimation()
{

}


void GifBulletSinStraight::UpdateCollision(Object* checkingObject)
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

float GifBulletSinStraight::Moving()
{
	return (float)((sin(m_Position.x * 3.14/80.0 ) * 100 + m_startPosition.y) - m_Position.y);
}

void GifBulletSinStraight:: UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
	m_Physic->setVelocityX((sin(m_Position.y * 3.14/80.0 ) * 100 + m_startPosition.x) - m_Position.x);
	m_Physic->setVelocityY(1.5f);
}

void GifBulletSinStraight::Update()
{

}

void GifBulletSinStraight::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void GifBulletSinStraight::Release()
{

}

GifBulletSinStraight::~GifBulletSinStraight()
{

}