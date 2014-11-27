#include "BossCenter.h"



BossCenter::BossCenter()
{

}

BossCenter::BossCenter(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void BossCenter::Initialize()
{
	m_AttackCounter = 50;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_CENTER);
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
	m_Position.z = 0.4f;
}

void BossCenter::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: // cant be attack by rambo bullet
		m_Sprite->UpdateAnimation(800);
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


void BossCenter::UpdateCollision(Object* checkingObject)
{
	switch (checkingObject->getID())
	{
		/*
			if(detectCollision with BulletRambo && stateObject == Alive)
			{
				m_attackCounter --;
			}
			if(m_AttackCounter == 0)
			{
				m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
			}
		*/
	default:
		break;
	}
}

void BossCenter:: UpdateMovement()
{}
void BossCenter::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
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
void BossCenter::Render(SPRITEHANDLE spriteHandle)
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


void BossCenter::Release()
{
	m_Sprite = 0;
	sprite_alive->Release();
	sprite_dead->Release();
}

BossCenter::~BossCenter()
{

}