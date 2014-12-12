#include "BulletSnipperWaterHiding.h"


BulletSnipperWaterHiding::BulletSnipperWaterHiding()
{

}

BulletSnipperWaterHiding::BulletSnipperWaterHiding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _id): DynamicObject(_position, _direction, _id)
{

}

void BulletSnipperWaterHiding::Initialize()
{
	this->m_sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	this->m_spite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOOM_EXPLOISION));
	this->m_sprite_main->setScale(0.7f);
	this->m_Position.z = 1.0f;
	this->m_Physic->setVelocityY(1.0f);
	this->m_DirectAttack = eDirectAttack::AD_TOP;
	m_Sprite = m_sprite_main;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	m_TimeChangeState = 0;
}

void BulletSnipperWaterHiding::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite->getAnimationAction()->setCurrentFrame(0);
		break;
	case STATE_BEFORE_DEATH:
		if(isDead == false)
		{
			isDead = true;
			m_Sprite = m_spite_dead;
		}
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}	
}

void BulletSnipperWaterHiding::UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
	
}

void BulletSnipperWaterHiding::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds(); 
		if(m_TimeChangeState > 4000)
		{
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_BOSS1, D3DXVECTOR3(m_Position.x + 30, m_Position.y + 50, 1), D3DXVECTOR2(0.3, -0.5),-5.76f);
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_BOSS1, D3DXVECTOR3(m_Position.x, m_Position.y + 50, 1), D3DXVECTOR2(-0.1, -0.5),-11.4f);
			BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_OF_BOSS1, D3DXVECTOR3(m_Position.x - 30, m_Position.y + 50, 1), D3DXVECTOR2(-0.3, -0.5),2.7f);
			m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
			m_Physic->setAccelerateY(0);
			m_Physic->setVelocityY(0);
			m_TimeChangeState = 0;
		}
		break;
	case STATE_BEFORE_DEATH:
		if(isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 1500)
			{
				m_ObjectState = eObjectState::STATE_DEATH;
			}
		}
		break;
	case STATE_DEATH:
		Release();
		break;
	default:
		break;
	}
}

void BulletSnipperWaterHiding::UpdateCollision(Object* checkingObject)
{

}

void BulletSnipperWaterHiding::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle,
				getPositionVec2(),
				m_Sprite->getSpriteEffect(),
				m_Sprite->getRotate(),
				m_Sprite->getScale(),
				m_Position.z);
	}
}

void BulletSnipperWaterHiding::Release()
{
	m_Sprite = NULL;
	m_spite_dead->Release();
	m_sprite_main->Release();
	SAFE_DELETE(m_spite_dead);
	SAFE_DELETE(m_sprite_main);
}

BulletSnipperWaterHiding::~BulletSnipperWaterHiding()
{

}
