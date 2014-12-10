#include "BulletSnipperWaterHiding.h"


BulletSnipperWaterHiding::BulletSnipperWaterHiding()
{

}

BulletSnipperWaterHiding::BulletSnipperWaterHiding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _id) : Bullet(_position, _direction, _id)
{

}

void BulletSnipperWaterHiding::Initialize()
{
	this->m_sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	this->m_spite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	this->m_Sprite->setScale(0.5f);
	this->m_Position.z = 1.0f;
	this->m_Physic->setVelocityX(2.0f);
	//this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
	this->m_TypeBullet = eIDTypeBullet::BULLET_SNIPPER_WATER_HIDING;
	this->m_DirectAttack = eDirectAttack::AD_TOP;
	this->m_factor = 0;
	m_isDead = false;
	m_Sprite = m_sprite_main;
	
}

void BulletSnipperWaterHiding::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite->getAnimationAction()->setCurrentFrame(0);
		break;
	case STATE_SHOOTING:
		m_Sprite->getAnimationAction()->setCurrentFrame(0);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = m_spite_dead;
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState >= 1000)
		{
			m_ObjectState = eObjectState::STATE_DEATH;
			m_TimeChangeState = 0;
		}
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		Release();
		break;
	default:
		break;
	}	
}

void BulletSnipperWaterHiding::UpdateMovement()
{
	//this->getPhysic()->UpdateMovement(&this->m_Position);
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

void BulletSnipperWaterHiding::Update()
{
	if(m_Position.y >= 400)
	{
		m_isDead = true;
	}
	if(m_isDead == true)
	{
		m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_SNIPPER_WATER_HIDING, this->m_Position, D3DXVECTOR2(-0.3f, 1.0f), -1.73);
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_SNIPPER_WATER_HIDING, this->m_Position, D3DXVECTOR2(-0.5f, 1.0f), -5.67);
		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_SNIPPER_WATER_HIDING, this->m_Position, D3DXVECTOR2(0.5f, 1.0f), 5.67);
		
		for(std::list<Bullet*>::iterator i = BulletPoolManager::getInstance()->m_ListBulletInGame.begin(); i != BulletPoolManager::getInstance()->m_ListBulletInGame.end(); ++i)
		{
			(*i)->getPhysic()->setAccelerateY(-2.5f);
		}
	}

}

void BulletSnipperWaterHiding::UpdateCollision(Object* checkingObject)
{}

void BulletSnipperWaterHiding::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite)
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
	m_spite_dead->Release();
	m_sprite_main->Release();
	m_Sprite = 0;
}

BulletSnipperWaterHiding::~BulletSnipperWaterHiding()
{

}
