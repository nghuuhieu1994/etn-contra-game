#include "SpaceShip.h"



SpaceShip::SpaceShip()
{

}

SpaceShip::SpaceShip(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void SpaceShip::Initialize()
{
	//m_AttackCounter = 20;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SPACE_SHIP));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
	m_Position.z = 0.4f;
}



void SpaceShip::UpdateAnimation()
{	
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: // cant be attack by rambo bullet
		//m_Sprite->UpdateAnimation(1000);
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


void SpaceShip::UpdateCollision(Object* checkingObject)
{
	//switch (checkingObject->getID())
	//{
	//	// checking collision with Bullet
	//	//m_AttackCounter--;
	//	/*
	//	if(m_AttackCounter == 0)
	//	{
	//		this->m_ObjectState == eObjectState::STATE_BEFORE_DETH;
	//	}
	//	*/
	//default:
	//	break;
	//}
}

void SpaceShip:: UpdateMovement()
{}
void SpaceShip::Update()
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
void SpaceShip::Render(SPRITEHANDLE spriteHandle)
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


void SpaceShip::Release()
{
	m_Sprite = 0;
	sprite_alive->Release();
	sprite_dead->Release();
}

SpaceShip::~SpaceShip()
{

}