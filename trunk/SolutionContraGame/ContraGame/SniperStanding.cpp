#include "SniperStanding.h"

SniperStanding::SniperStanding()
{
}

SniperStanding::SniperStanding(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	//m_Physic = new Physic();
	m_Position = _position;
	//m_Physic->setPosition(_position);// tach position ra khoi Physic
}

void SniperStanding::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_bot = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_BOT));
	sprite_top = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_TOP));
	sprite_mid = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_MID));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));

	/*
	Bullet[0] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[1] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[2] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[3] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[4] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[5] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[6] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[7] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[8] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[9] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[10] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[11] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[12] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[13] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	Bullet[14] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET_BIG));
	*/
	m_canAttack = false;
}

void SniperStanding::UpdateAnimation()
{
	if(Rambo_X < m_Position.x)
		m_Direction = eDirection::LEFT;

	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		if(Rambo_Y > m_Position.y + 50)
			m_Sprite = sprite_top;
		else
		{
			if(abs(Rambo_X - m_Position.x) < 100)
				m_Sprite = sprite_bot;
			else
				m_Sprite = sprite_mid;
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
		m_Sprite->setSpriteEffect(ESpriteEffect::None);
	else
	{
		if(m_Direction == eDirection::RIGHT)
			m_Sprite->setSpriteEffect(ESpriteEffect::Horizontally);
	}
}
void SniperStanding::UpdateMovement()
{

}
void SniperStanding::UpdateCollision(Object* checkingObject)
{
	switch (checkingObject->getID())
	{
	case eObjectID::RAMBO:
		Rambo_X = (int)(((Rambo*)checkingObject)->getPositionVec2().x);
		Rambo_Y = (int)(((Rambo*)checkingObject)->getPositionVec2().y);

		// do a realthing?
		break;
	default:
		break;
	}
}

void SniperStanding::Update()
{
	this->UpdateAnimation();

	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 1000)
		{
			m_TimeChangeState = 0;
			m_ObjectState = eObjectState::STATE_SHOOTING;
		}
		break;
	case STATE_SHOOTING:
		m_TimeChangeState += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(m_TimeChangeState > 500)
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