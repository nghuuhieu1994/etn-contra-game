#include "GifBulletMoving.h"

GifBulletMoving::GifBulletMoving()
{

}

GifBulletMoving::GifBulletMoving(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	//m_Physic = new Physic();
	//m_Physic->setPosition(_position);
	
	m_startPosition = _position;
	
}

void GifBulletMoving::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GIF_BULLET_MOVING));
}

void GifBulletMoving::UpdateAnimation()
{

}


void GifBulletMoving::UpdateCollision(Object* checkingObject)
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

float GifBulletMoving::Moving()
{
	return (float)((sin(m_Position.x * 3.14/80.0 ) * 100 + m_startPosition.y) - m_Position.y);
}

void GifBulletMoving:: UpdateMovement()
{
	//
	//m_Physic->setVelocity(D3DXVECTOR2(1.5f, m_Physic->getVelocity().y));
	m_Physic->UpdateMovement(&m_Position);
	m_Physic->setVelocityY((sin(m_Position.x * 3.14/80.0 ) * 100 + m_startPosition.y) - m_Position.y);
	m_Physic->setVelocityX(1.5f);
	
	//Sin(m_Position);
}

void GifBulletMoving::Update()
{

}

void GifBulletMoving::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void GifBulletMoving::Release()
{

}

GifBulletMoving::~GifBulletMoving()
{

}