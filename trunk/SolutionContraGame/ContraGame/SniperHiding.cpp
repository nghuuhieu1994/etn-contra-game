#include "SniperHiding.h"


SniperHiding::SniperHiding()
{

}

SniperHiding::SniperHiding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
	
}

void SniperHiding::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive_hiding = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_HIDING));
	//sprite_alive_shooting = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_SHOOTING));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	//m_Sprite = sprite_alive_shooting;
}

void SniperHiding::UpdateAnimation()
{	
	if(CGlobal::Rambo_X < m_Position.x)
		m_Direction = eDirection::LEFT;
	else
		m_Direction = eDirection::RIGHT;

	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: // cant be attack by rambo bullet
		m_Sprite = sprite_alive_hiding;
		_distance_X = (int)(abs(CGlobal::Rambo_X - this->getPositionVec2().x));
		//if( _distance_X > 350)
		//{
		//	//m_Sprite->getAnimation()->setIndexStart(0);
		//	//m_Sprite->getAnimation()->setIndexEnd(1);
		//	m_Sprite->getAnimation()->setCurrentFrame(0);
		//}
		//else if(_distance_X < 350)
		//{
		//	m_Sprite->getAnimation()->setIndexStart(0);
		//	m_Sprite->getAnimation()->setIndexEnd(1);
		//}
		this->getSprite()->getAnimation()->setCurrentFrame(1);
		m_Sprite->UpdateAnimation(500);
		break;
	case STATE_SHOOTING:
		//m_Sprite = sprite_alive_shooting;
		m_Sprite = sprite_alive_hiding;
		this->getSprite()->getAnimation()->setCurrentFrame(0);
		m_Sprite->UpdateAnimation(500);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(120);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}	
	if(m_Direction == eDirection::LEFT)
		m_Sprite->setSpriteEffect(ESpriteEffect::None);
	else
	{
		if(m_Direction == eDirection::RIGHT)
			m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
	}
}


void SniperHiding::UpdateCollision(Object* checkingObject)
{
	/*IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch(checkingObject->getTypeObject())
		{
		case ETypeObject::DYNAMIC_OBJECT:
			switch (checkingObject->getID())
			{
			case eObjectID ::BULLET_RAMBO:
				if(collideDirection == IDDirection::DIR_TOP)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					break;
				}
				else if(collideDirection == IDDirection::DIR_BOTTOM)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					break;
				}

				else if(collideDirection == IDDirection::DIR_LEFT)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					break;
				}

				else if(collideDirection == IDDirection::DIR_RIGHT)
				{
					m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
					break;
				}
				break;

			default:
				break;
			}

		default:
				break;	
		}
	}*/
}

void SniperHiding:: UpdateMovement()
{}

void SniperHiding::Update()
{
	_distance_X = (int)(abs(CGlobal::Rambo_X - this->getPositionVec2().x));
	if(_distance_X < 350)
	{
		switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 2000)
		{
			m_TimeChangeState = 0;
			m_ObjectState = eObjectState::STATE_SHOOTING;
		}
		break;
	case STATE_SHOOTING:
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 4000)
		{
			m_TimeChangeState = 0;
			m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
		}
		break;
	case STATE_BEFORE_DEATH:
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 1000)
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
	
}
void SniperHiding::Render(SPRITEHANDLE spriteHandle)
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


void SniperHiding::Release()
{
	m_Sprite = 0;
	sprite_alive_hiding->Release();
	//sprite_alive_shooting->Release();
	sprite_dead->Release();
}

SniperHiding::~SniperHiding()
{

}