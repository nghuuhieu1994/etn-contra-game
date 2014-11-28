#include "FireBullet.h"


FireBullet::FireBullet()
{

}

FireBullet::FireBullet(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) : Bullet(_position, _direction, _objectID)
{
	//m_Position.z = 0.4f;
}

void FireBullet::reset()
{
	Bullet::reset();

	this->m_VelocityOfOrigin = D3DXVECTOR2(0.0f, 0.0f);
	this->m_Angle = 0.0f;
	this->m_PositionOfOrigin = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

}

void FireBullet::Initialize()
{
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_FIRE_BULLET_RAMBO));
	this->m_Sprite->setScale(0.5f);
	m_Position.z = 0.4f;
	this->m_Physic->setVelocityX(2.0f);
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
	this->m_TypeBullet = eIDTypeBullet::FIRE_BULLET_OF_RAMBO;
	this->m_DirectAttack = eDirectAttack::AD_TOP;
	this->m_factor = 0;
	this->m_Angle = 0;
}

void FireBullet::UpdateMovement()
{
	Bullet::UpdateMovement();

	D3DXVECTOR3 tempPosition;

	if(this->m_factor == 100)
	{
		this->m_VelocityOfOrigin.x = 0.0f;
		tempPosition = D3DXVECTOR3(this->m_PositionOfOrigin.x + 40 * cos(this->m_Angle), this->m_PositionOfOrigin.y + 40 * sin(this->m_Angle), 1.0f);
		this->getPhysic()->setVelocityX(this->m_PositionOfOrigin.x + 40 * cos(this->m_Angle) - this->m_Position.x);
		this->getPhysic()->setVelocityY(this->m_PositionOfOrigin.y + 40 * sin(this->m_Angle) - this->m_Position.y);
		this->m_PositionOfOrigin.y += this->m_VelocityOfOrigin.y;
		this->m_Angle += 0.2f;
	}
	else if(this->m_factor == 0)
	{
		this->m_VelocityOfOrigin.y = 0.0f;
		tempPosition = D3DXVECTOR3(this->m_PositionOfOrigin.x + 40 * cos(this->m_Angle), this->m_PositionOfOrigin.y + 40 * sin(this->m_Angle), 1.0f);
		this->getPhysic()->setVelocityX(this->m_PositionOfOrigin.x + 40 * cos(this->m_Angle) - this->m_Position.x);
		this->getPhysic()->setVelocityY(this->m_PositionOfOrigin.y + 40 * sin(this->m_Angle) - this->m_Position.y);
		this->m_PositionOfOrigin.x += this->m_VelocityOfOrigin.x;
		this->m_Angle += 0.2f;
	}
	else
	{
		//this->m_VelocityOfOrigin.y = 0.0f;
		tempPosition = D3DXVECTOR3(this->m_PositionOfOrigin.x + 40 * cos(this->m_Angle), this->m_PositionOfOrigin.y + 40 * sin(this->m_Angle), 1.0f);
		this->getPhysic()->setVelocityX(this->m_PositionOfOrigin.x + 40 * cos(this->m_Angle) - this->m_Position.x);
		this->getPhysic()->setVelocityY(this->m_PositionOfOrigin.y + 40 * sin(this->m_Angle) - this->m_Position.y);
		this->m_PositionOfOrigin.x += this->m_VelocityOfOrigin.x;
		float tempValue = this->m_PositionOfOrigin.x - this->m_StartPosition.x;
		this->m_PositionOfOrigin.y = this->m_factor * tempValue + this->m_StartPosition.y;
		this->m_Angle += 0.2f;
	}
}

FireBullet::~FireBullet()
{

}
