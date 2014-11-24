#include "GifBulletStatic.h"

GifBulletStatic::GifBulletStatic()
{

}

GifBulletStatic::GifBulletStatic(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: DynamicObject(_position, _direction, _objectID)
{
}

void GifBulletStatic::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GIF_BULLET_STATIC));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
}

void GifBulletStatic::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: // cant be attack by rambo bullet
		if(abs(CGlobal::Rambo_X - this->getPositionVec2().x) > 100)
		{
			 this->getSprite()->getAnimation()->setCurrentFrame(0);
		}
		else
		{
			 this->getSprite()->getAnimation()->setIndexStart(0);
			 this->getSprite()->getAnimation()->setIndexEnd(6);
		}

		m_Sprite->UpdateAnimation(500);
		break;
	case STATE_BEFORE_DEATH:
		if (!isDead)
		{
			m_Sprite = sprite_dead;
			isDead = true;
		}
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}


void GifBulletStatic::UpdateCollision(Object* checkingObject)
{
	if (!isDead)
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
		if (collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			default:
				break;
			}

		}
	}
}

void GifBulletStatic:: UpdateMovement()
{}
void GifBulletStatic::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_BEFORE_DEATH:
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 1000)
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
void GifBulletStatic::Render(SPRITEHANDLE spriteHandle)
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


void GifBulletStatic::Release()
{
	m_Sprite = 0;
	sprite_alive->Release();
	sprite_dead->Release();
}

GifBulletStatic::~GifBulletStatic()
{

}