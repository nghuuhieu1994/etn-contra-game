//#include "BulletSnipperWaterHiding.h"
//
//
//BulletSnipperWaterHiding::BulletSnipperWaterHiding()
//{
//
//}
//
//BulletSnipperWaterHiding::BulletSnipperWaterHiding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _id) : Bullet(_position, _direction, _id)
//{
//
//}
//
//void BulletSnipperWaterHiding::Initialize()
//{
//	this->m_sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
//	this->m_spite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
//	this->m_Sprite->setScale(0.5f);
//	this->m_Position.z = 1.0f;
//	this->m_Physic->setVelocityX(2.0f);
//	this->m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.0f));
//	this->m_TypeBullet = eIDTypeBullet::BULLET_SNIPPER_WATER_HIDING;
//	this->m_DirectAttack = eDirectAttack::AD_LEFT;
//	this->m_factor = 0;
//	m_isDead = false;
//	m_Sprite = m_sprite_main;
//	
//}
//
//void BulletSnipperWaterHiding::UpdateAnimation()
//{
//	switch (m_ObjectState)
//	{
//	case STATE_ALIVE_IDLE:
//		m_Sprite->getAnimationAction()->setCurrentFrame(0);
//		break;
//	case STATE_SHOOTING:
//		m_Sprite->getAnimationAction()->setCurrentFrame(0);
//		break;
//	case STATE_BEFORE_DEATH:
//		m_Sprite = m_spite_dead;
//		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
//		if(m_TimeChangeState >= 1000)
//		{
//			m_ObjectState = eObjectState::STATE_DEATH;
//			m_TimeChangeState = 0;
//		}
//		m_Sprite->UpdateAnimation(250);
//		break;
//	case STATE_DEATH:
//		Release();
//		break;
//	default:
//		break;
//	}	
//}
//
//void BulletSnipperWaterHiding::UpdateMovement()
//{
//	this->getPhysic()->UpdateMovement(&this->m_Position);
//}
//
//void BulletSnipperWaterHiding::Update()
//{
//	if(m_Position.y >= 400)
//	{
//		m_isDead = true;
//	}
//	if(m_isDead == true)
//	{
//		//bullet1 = new BulletSnipperWaterHiding(this->m_Position, eDirection::LEFT, eObjectID::BULLET_SNIPPER_WATER_HIDING,
//		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_SNIPPER_WATER_HIDING, this->m_Position, D3DXVECTOR2(-0.3f, 1.0f), -1.73);
//		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_SNIPPER_WATER_HIDING, this->m_Position, D3DXVECTOR2(-0.5f, 1.0f), -5.67);
//		BulletPoolManager::getInstance()->addBulletIntoList(eIDTypeBullet::BULLET_SNIPPER_WATER_HIDING, this->m_Position, D3DXVECTOR2(0.5f, 1.0f), 5.67);
//		
//		for(std::list<Bullet*>::iterator i = BulletPoolManager::getInstance()->m_ListBulletInGame.begin(); i != BulletPoolManager::getInstance()->m_ListBulletInGame.end(); ++i)
//		{
//			(*i)->getPhysic()->setAccelerateY(-0.5f);
//		}
//	}
//
//}
//
//
//
//BulletSnipperWaterHiding::~BulletSnipperWaterHiding()
//{
//
//}
