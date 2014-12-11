#include "BulletSnipperWaterHiding.h"


BulletSnipperWaterHiding::BulletSnipperWaterHiding()
{

}

BulletSnipperWaterHiding::BulletSnipperWaterHiding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _id): Bullet(_position, _direction, _id)
{

}

void BulletSnipperWaterHiding::Initialize()
{
	this->m_sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	this->m_spite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	this->m_sprite_main->setScale(0.6f);
	this->m_Position.z = 1.0f;
	this->m_Physic->setVelocityY(1.0f);
	this->m_TypeBullet = eIDTypeBullet::BULLET_OF_SNIPPER_WATER_HIDING;
	this->m_DirectAttack = eDirectAttack::AD_TOP;
	isDead = false;
	m_Sprite = m_sprite_main;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	m_TimeChangeState = 0;
	bullet1 = new BulletSnipperWaterHiding(D3DXVECTOR3(m_Position.x - 20, m_Position.y + 300, 1), eDirection::TOP, eObjectID::BULLET_SNIPPER_WATER_HIDING);
	bullet2 = new BulletSnipperWaterHiding(D3DXVECTOR3(m_Position.x, m_Position.y + 300, 1), eDirection::TOP, eObjectID::BULLET_SNIPPER_WATER_HIDING);
	bullet3 = new BulletSnipperWaterHiding(D3DXVECTOR3(m_Position.x + 20, m_Position.y + 300, 1), eDirection::TOP, eObjectID::BULLET_SNIPPER_WATER_HIDING);
	bullet1->m_Physic->setVelocityX(-0.4f);
	bullet1->m_Physic->setVelocityY(0.7f);
	bullet1->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	bullet2->m_Physic->setVelocityX(0.2f);
	bullet2->m_Physic->setVelocityY(0.7f);
	bullet2->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));
	bullet3->m_Physic->setVelocityX(0.4f);
	bullet3->m_Physic->setVelocityY(0.7f);
	bullet3->m_Physic->setAccelerate(D3DXVECTOR2(0, -0.01f));

}

void BulletSnipperWaterHiding::UpdateAnimation()
{
	if(bullet1 != NULL && bullet2 != NULL && bullet3 != NULL)
		{
			bullet1->UpdateAnimation();
			bullet2->UpdateAnimation();
			bullet3->UpdateAnimation();
		}
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite->getAnimationAction()->setCurrentFrame(0);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = m_spite_dead;
		m_Sprite->UpdateAnimation(250);
		break;
	default:
		break;
	}	
}

void BulletSnipperWaterHiding::UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
	if(bullet1 != NULL && bullet2 != NULL && bullet3 != NULL)
	{
		bullet1->UpdateMovement();
		bullet2->UpdateMovement();
		bullet3->UpdateMovement();
	}
	
}

void BulletSnipperWaterHiding::Update()
{
	if(bullet1 != NULL && bullet2 != NULL && bullet3 != NULL)
	{
		bullet1->Update();
		bullet2->Update();
		bullet3->Update();
	}		
	switch (m_ObjectState)
	{

	case STATE_ALIVE_IDLE:
		m_TimeChangeState = CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 1000)
		{
			m_isDead = true;
			m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
			m_TimeChangeState = 0;
		}
		break;
	case STATE_BEFORE_DEATH:
		m_TimeChangeState = CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 1500)
		{
			isDead = true;
			m_ObjectState = eObjectState::STATE_DEATH;
		}
		break;
	case STATE_DEATH:
		if(this->m_Sprite != 0)
			this->Release();
		break;
	default:
		break;
	}
}

void BulletSnipperWaterHiding::UpdateCollision(Object* checkingObject)
{
	if( isDead != true )
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

		if(collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
				case eObjectID::TILE_BASE:
					if(collideDirection == IDDirection::DIR_TOP)
						//m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					    //isDead = true;
					break;
				default:
					break;
			}
		}
	}
	
}

void BulletSnipperWaterHiding::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0 && isDead == false)
	{
		m_Sprite->Render(spriteHandle,
				getPositionVec2(),
				m_Sprite->getSpriteEffect(),
				m_Sprite->getRotate(),
				m_Sprite->getScale(),
				m_Position.z);
	}
	if(m_ObjectState == eObjectState::STATE_BEFORE_DEATH && bullet1 != NULL && bullet2 != NULL && bullet3 != NULL)
	{
		bullet1->Render(spriteHandle);
		bullet2->Render(spriteHandle);
		bullet3->Render(spriteHandle);
		//m_isDead = false;
	}
}

void BulletSnipperWaterHiding::Release()
{
	m_spite_dead->Release();
	m_sprite_main->Release();
	SAFE_DELETE(m_spite_dead);
	SAFE_DELETE(m_sprite_main);
	//bullet1->Release();
	//bullet2->Release();
	//bullet3->Release();
	m_Sprite = 0;
}

BulletSnipperWaterHiding::~BulletSnipperWaterHiding()
{

}
