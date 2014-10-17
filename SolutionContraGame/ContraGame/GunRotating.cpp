#include "GunRotating.h"



GunRotating::GunRotating()
{

}

GunRotating::GunRotating(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
	//m_Position = _position;
}

void GunRotating::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GUN_ROTATING));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
}

void GunRotating::UpdateAnimation()
{	
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: // cant be attack by rambo bullet
		m_Sprite = sprite_alive;
		_distance_X = abs(Rambo_X - this->getPositionVec2().x);
		_distance_Y = Rambo_Y - this->getPositionVec2().y;
		if( _distance_X > 350)
		{
			// block status
			m_Sprite->getAnimation()->setIndexStart(0);
			m_Sprite->getAnimation()->setIndexEnd(1);
		}
		else
		{
			if(_distance_X <= 350 && _distance_X > 300)
			{
				if(Rambo_X < getPositionVec2().x)
				{
					m_Sprite->getAnimation()->setIndexStart(2);
					m_Sprite->getAnimation()->setIndexEnd(2);
					m_Sprite->getAnimation()->setCurrentFrame(2);
				}
				else
				{
					m_Sprite->getAnimation()->setIndexStart(8);
					m_Sprite->getAnimation()->setIndexEnd(8);
					m_Sprite->getAnimation()->setCurrentFrame(8);
				}
			}
			else
			{
				if(_distance_X <= 300 && _distance_X > 100)
				{
					if(Rambo_X < getPositionVec2().x)
					{
						if(_distance_Y <= 0)
						{
							m_Sprite->getAnimation()->setIndexStart(13);
							m_Sprite->getAnimation()->setIndexEnd(13);
							m_Sprite->getAnimation()->setCurrentFrame(13);
						}
						else
						{
							m_Sprite->getAnimation()->setIndexStart(3);
							m_Sprite->getAnimation()->setIndexEnd(3);
							m_Sprite->getAnimation()->setCurrentFrame(3);
						}
					}
					else
					{
						if(_distance_Y <= 0)
						{
							m_Sprite->getAnimation()->setIndexStart(9);
							m_Sprite->getAnimation()->setIndexEnd(9);
							m_Sprite->getAnimation()->setCurrentFrame(9);
						}
						else
						{
							m_Sprite->getAnimation()->setIndexStart(7);
							m_Sprite->getAnimation()->setIndexEnd(7);
							m_Sprite->getAnimation()->setCurrentFrame(7);
						}
					}
				}
				else
				{
					if(_distance_X <= 100 && _distance_X > 20)
					{
						if(Rambo_X < getPositionVec2().x)
						{
							if(_distance_Y <= 0)
							{
								m_Sprite->getAnimation()->setIndexStart(12);
								m_Sprite->getAnimation()->setIndexEnd(12);
								m_Sprite->getAnimation()->setCurrentFrame(12);
							}
							else
							{
								m_Sprite->getAnimation()->setIndexStart(4);
								m_Sprite->getAnimation()->setIndexEnd(4);
								m_Sprite->getAnimation()->setCurrentFrame(4);
							}
						}
						else
						{
							if(_distance_Y <= 0)
							{
								m_Sprite->getAnimation()->setIndexStart(10);
								m_Sprite->getAnimation()->setIndexEnd(10);
								m_Sprite->getAnimation()->setCurrentFrame(10);
							}
							else
							{
								m_Sprite->getAnimation()->setIndexStart(6);
								m_Sprite->getAnimation()->setIndexEnd(6);
								m_Sprite->getAnimation()->setCurrentFrame(6);
							}
						}
					}
					else
					{
						if(_distance_Y < 0)
						{
							m_Sprite->getAnimation()->setIndexStart(11);
							m_Sprite->getAnimation()->setIndexEnd(11);
							m_Sprite->getAnimation()->setCurrentFrame(11);
						}
						else
						{
							m_Sprite->getAnimation()->setIndexStart(5);
							m_Sprite->getAnimation()->setIndexEnd(5);
							m_Sprite->getAnimation()->setCurrentFrame(5);
						}
					}
				}
			}

		}
		m_Sprite->UpdateAnimation(1000);
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
}


void GunRotating::UpdateCollision(Object* checkingObject)
{
	switch (checkingObject->getID())
	{
	case eObjectID::RAMBO:
		Rambo_X = checkingObject->getPositionVec2().x;
		Rambo_Y = checkingObject->getPositionVec2().y;
		m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
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