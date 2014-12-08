#include "BulletBoss1.h"


BulletBoss1::BulletBoss1()
{

}

BulletBoss1::BulletBoss1(D3DXVECTOR3 _position, eDirection _direction, eObjectID _id) : Bullet(_position, _direction, _id)
{

}

void BulletBoss1::Initialize()
{
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	this->m_Sprite->setScale(0.7f);
	this->m_Position.z = 1.0f;
	this->m_Physic->setVelocityX(2.0f);
	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
	this->m_TypeBullet = eIDTypeBullet::BULLET_OF_BOSS1;
	this->m_DirectAttack = eDirectAttack::AD_LEFT;
	this->m_factor = 0;
}

void BulletBoss1::UpdateMovement()
{
	this->getPhysic()->UpdateMovement(&this->m_Position);
}

BulletBoss1::~BulletBoss1()
{

}
