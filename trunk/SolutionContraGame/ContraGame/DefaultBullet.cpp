#include "DefaultBullet.h"


DefaultBullet::DefaultBullet()
{

}
DefaultBullet::DefaultBullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : Bullet(_position, _direction, _objectID)
{
	this->m_Position.z = 1.0f;
}

void DefaultBullet::Initialize()
{
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_DEFAULT_BULLET_RAMBO));
	this->m_Position.z = 1.0f;
	this->m_Physic->setVelocityX(2.0f);
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
	this->m_TypeBullet = eIDTypeBullet::DEFAULT_BULLET_OF_RAMBO;
	// because object class has a directattack
	// don't use directack
	this->m_DirectAttack = eDirectAttack::AD_TOP;
	this->m_factor = 0;
}

void DefaultBullet::UpdateMovement()
{
	Bullet::UpdateMovement();
	D3DXVECTOR3 tempPosition;

	if(this->m_factor == 100)
	{
		this->getPhysic()->setVelocityX(0.0f);
	}
	else if(this->m_factor == 0)
	{
		this->getPhysic()->setVelocityY(0.0f);
	}
	else
	{
		tempPosition = D3DXVECTOR3(this->m_Position.x + this->getPhysic()->getVelocity().x - this->m_StartPosition.x, 0.0f, 0.0f);
		tempPosition.y = this->m_factor * tempPosition.x;
		this->getPhysic()->setVelocityY((tempPosition.y + this->m_StartPosition.y - this->m_Position.y));
	}
}

DefaultBullet::~DefaultBullet()
{

}
