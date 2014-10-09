#include "SniperStanding.h"

SniperStanding::SniperStanding()
{
}

SniperStanding::SniperStanding(D3DXVECTOR3 _position, eDirection _direction) : Object(_position, _direction)
{
}

void SniperStanding::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_bot = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_BOT));
	sprite_top = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_TOP));
	sprite_mid = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SNIPER_STANDING_MID));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	
}

void SniperStanding::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite = sprite_mid;
		//m_Sprite->UpdateAnimation(400);
		break;
	case STATE_ATTACK:
		break;
	case STATE_BEFORE_DEATH:
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void SniperStanding::UpdateMovement()
{
	
}

void SniperStanding::UpdateCollision(Object* checkingObject)
{
}


void SniperStanding::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != NULL)
	{
		m_Sprite->Render(spriteHandle, m_Physic->getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Physic->getPositionVec3().z);
	}
}
void SniperStanding::Release()
{
	m_Sprite = NULL;
	sprite_bot->Release();
	sprite_dead->Release();
	sprite_top->Release();
	sprite_mid->Release();
}
SniperStanding::~SniperStanding()
{}