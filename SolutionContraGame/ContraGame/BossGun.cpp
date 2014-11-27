#include "BossGun.h"



BossGun::BossGun()
{

}

BossGun::BossGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void BossGun::Initialize()
{
	m_AttackCounter = 20;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GUN_BOSS));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
	m_Position.z = 0.4f;
	isShoot = false;
}

void BossGun::Shoot()
{
	// typesome fucking code to add bullet ---> pollBullet
}

D3DXVECTOR3 BossGun::GetStartPositionOfBullet()
{
	return D3DXVECTOR3(m_Position.x - 20, m_Position.y, m_Position.z);
}


void BossGun::UpdateAnimation()
{	
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: // cant be attack by rambo bullet
		m_Sprite->UpdateAnimation(1000);
		break;
	case STATE_SHOOTING:
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}	
}


void BossGun::UpdateCollision(Object* checkingObject)
{
	switch (checkingObject->getID())
	{
		// checking collision with Bullet
		//m_AttackCounter--;
		/*
		if(m_AttackCounter == 0)
		{
			this->m_ObjectState == eObjectState::STATE_BEFORE_DETH;
		}
		*/
	default:
		break;
	}
}

void BossGun:: UpdateMovement()
{}
void BossGun::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 800)
		{
			m_TimeChangeState = 0;
			m_ObjectState = eObjectState::STATE_SHOOTING;
			isShoot = true;
		}
		break;
	case STATE_SHOOTING:
		if(isShoot == true)
		{
			Shoot();
			isShoot = false;
		}
		else
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 200)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
			}
		}
		break;
	case STATE_BEFORE_DEATH:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 1500)
		{
			m_ObjectState = eObjectState::STATE_DEATH;
			m_TimeChangeState = 0;
		}
		break;
	case STATE_DEATH:
		this->Release();
		break;
	default:
		break;
	}
}
void BossGun::Render(SPRITEHANDLE spriteHandle)
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


void BossGun::Release()
{
	m_Sprite = 0;
	sprite_alive->Release();
	sprite_dead->Release();
}

BossGun::~BossGun()
{

}