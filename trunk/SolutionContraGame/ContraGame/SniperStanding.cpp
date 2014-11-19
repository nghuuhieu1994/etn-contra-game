#include "SniperStanding.h"

SniperStanding::SniperStanding()
{
}

SniperStanding::SniperStanding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void SniperStanding::Shoot()
{
	switch (m_DirectAttack)
	{
	case AD_LEFT:
		break;
	case AD_RIGHT:
		break;
	case AD_TOP_LEFT:
		break;
	case AD_TOP_RIGHT:
		break;
	case AD_BOTTOM_LEFT:
		break;
	case AD_BOTTOM_RIGHT:
		break;
	default:
		break;	
	}
}

D3DXVECTOR3 SniperStanding::GetStartPositionOfBullet()
{
	switch(m_DirectAttack)
	{
	case AD_LEFT:
		return D3DXVECTOR3(m_Position.x - 8, m_Position.y + 20, 0); 
		break;
	case AD_RIGHT:
		return D3DXVECTOR3(m_Position.x + 8, m_Position.y + 20, 0);
		break;
	case AD_TOP_LEFT:
		return D3DXVECTOR3(m_Position.x - 10, m_Position.y + 25, 0);
		break;
	case AD_TOP_RIGHT:
		return D3DXVECTOR3(m_Position.x + 10, m_Position.y + 25, 0);
		break;
	case AD_BOTTOM_LEFT:
		return D3DXVECTOR3(m_Position.x - 15, m_Position.y  , 0); 
		break;
	case AD_BOTTOM_RIGHT:
		return D3DXVECTOR3(m_Position.x + 15, m_Position.y , 0); 
		break;

	default:
		break;	
	}
}


void SniperStanding::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_bot = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_BOT));
	sprite_top = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_TOP));
	sprite_mid = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_MID));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));

	m_Sprite = sprite_mid;
}

void SniperStanding::UpdateAnimation()
{
	_distance_X = (int)(abs(CGlobal::Rambo_X - this->getPositionVec2().x));
	_distance_Y = (int)(abs(CGlobal::Rambo_Y - this->getPositionVec2().y));
	if(CGlobal::Rambo_X < m_Position.x)
	{
		m_Direction = eDirection::LEFT;
		if(m_Sprite == sprite_bot)
			m_DirectAttack = eDirectAttack::AD_BOTTOM_LEFT;
		if(m_Sprite == sprite_mid)
			m_DirectAttack = eDirectAttack::AD_LEFT;
		if(m_Sprite == sprite_top)
			m_DirectAttack = eDirectAttack::AD_TOP_LEFT;
	}
	else
	{
		m_Direction = eDirection::RIGHT;
		if(m_Sprite == sprite_bot)
				m_DirectAttack = eDirectAttack::AD_BOTTOM_RIGHT;
			if(m_Sprite == sprite_mid)
				m_DirectAttack = eDirectAttack::AD_RIGHT;
			if(m_Sprite == sprite_top)
				m_DirectAttack = eDirectAttack::AD_TOP_RIGHT;
	}

	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_TimeChangeDirectAttack += (int)(CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds());
		if (m_TimeChangeDirectAttack > 1500)
		{
			if(CGlobal::Rambo_Y > m_Position.y + 50)
			{
				m_Sprite = sprite_top;
			}
			else
			{
				if(abs(CGlobal::Rambo_X - m_Position.x) < 100)
					m_Sprite = sprite_bot;
				else
					m_Sprite = sprite_mid;
			}
			m_TimeChangeDirectAttack = 0;
		}
		break;
	case STATE_SHOOTING:
		m_Sprite->UpdateAnimation(900);
		break;
	case STATE_BEFORE_DEATH:
		m_Sprite = sprite_dead;
		m_Sprite->UpdateAnimation(500);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
	if(m_Direction == eDirection::LEFT)
	{
		m_Sprite->setSpriteEffect(ESpriteEffect::None);

	}
	else
	{
		m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
	}
}
void SniperStanding::UpdateMovement()
{

}
void SniperStanding::UpdateCollision(Object* checkingObject)
{
	IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

	if(collideDirection != IDDirection::DIR_NONE)
	{
		switch (checkingObject->getID())
		{
			case eObjectID ::BULLET_RAMBO:
				m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
				break;
			default:
				break;
		}

	}
}

void SniperStanding::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 3000)
		{
			m_TimeChangeState = 0;
			m_ObjectState = eObjectState::STATE_SHOOTING;
			isShoot = true;
		}
		break;
	case STATE_SHOOTING:
		if(isShoot == true && _distance_X < 300)
		{
			Shoot();
			isShoot = false;
		}
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 2500)
		{
			m_TimeChangeState = 0;
			
			m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
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
	}
}

void SniperStanding::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}
void SniperStanding::Release()
{
	m_Sprite = 0;
	sprite_bot->Release();
	sprite_dead->Release();
	sprite_top->Release();
	sprite_mid->Release();
}
SniperStanding::~SniperStanding()
{

}