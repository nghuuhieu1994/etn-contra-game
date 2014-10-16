#include "GunRotating.h"

GunRotating::GunRotating()
{

}

GunRotating::GunRotating(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position = _position;
}

void GunRotating::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GUN_ROTATING));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
}

void GunRotating::UpdateAnimation()
{
	//m_Sprite->UpdateAnimation(300);	
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: // cant be attack by rambo bullet
		m_Sprite = sprite_alive;
		//m_Sprite->UpdateAnimation(500);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(200);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}


void GunRotating::UpdateCollision(Object* checkingObject)
{
	switch (checkingObject->getID())
	{
	case eObjectID::RAMBO:
		// do something
		break;
	case eObjectID::BULLET_RAMBO:

		break;
	default:
		break;
	}
}

void GunRotating:: UpdateMovement()
{}
void GunRotating::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		if(abs(CGlobal::Rambo_X - this->getPositionVec2().x) > 300)
		{
			 this->getSprite()->getAnimation()->setIndexStart(0);
			 this->getSprite()->getAnimation()->setIndexEnd(1);
		}
		else
		{
			if(CGlobal::Rambo_Y <= this->getPositionVec2().y)
			{
				 if(abs(CGlobal::Rambo_X - this->getPositionVec2().x) > 200)
				 {
					 this->getSprite()->getAnimation()->setCurrentFrame(2);
				 }
				 else
				 {
					 if(abs(CGlobal::Rambo_X - this->getPositionVec2().x) > 150)
					 {
						this->getSprite()->getAnimation()->setCurrentFrame(2);
					 }
					 else
					 {
					 }
				 }
			}
		}
		break;
	case STATE_BEFORE_DEATH:
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 1500)
		{
			m_TimeChangeState = 0;
			m_ObjectState = eObjectState::STATE_DEATH;
		}
		break;
	case STATE_DEATH:
		this->Release();
		break;
	default:
		break;
	}
}
void GunRotating::Render(SPRITEHANDLE spriteHandle)
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


void GunRotating::Release()
{
	m_Sprite = 0;
	sprite_alive->Release();
	sprite_dead->Release();
}

GunRotating::~GunRotating()
{

}