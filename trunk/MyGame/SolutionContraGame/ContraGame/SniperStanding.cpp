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

	Bullet[0] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[1] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[2] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[3] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[4] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[5] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[6] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[7] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[8] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[9] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[10] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[11] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[12] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[13] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));
	Bullet[14] = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BULLET));

	m_canAttack = false;
}

void SniperStanding::UpdateAnimation()
{
	//if(CGlobal::RamboPosition.x < m_Physic->getPositionVec2().x)
	//	m_Direction = eDirection::LEFT;
	//else
	//	m_Direction = eDirection::RIGHT;

	//switch (m_ObjectState)
	//{
	//case STATE_ALIVE_IDLE:

	//	if(CGlobal::RamboPosition.y > m_Physic->getPositionVec2().y + 50)
	//		m_Sprite = sprite_top;
	//	else
	//	{
	//		if(abs(CGlobal::RamboPosition.x - m_Physic->getPositionVec2().x) < 100)
	//			m_Sprite = sprite_bot;
	//		else
	//			m_Sprite = sprite_mid;
	//	}
	//	m_Sprite->UpdateAnimation(500);
	//	


	//	break;
	//case STATE_BEFORE_DEATH:
	//	m_Sprite = sprite_dead;
	//	m_Sprite->UpdateAnimation(500);
	//	break;
	//case STATE_DEATH:

	//	break;
	//default:
	//	break;
	//}
	//if(m_Direction == eDirection::LEFT)
	//	m_Sprite->setSpriteEffect(eSpriteEffect::None);
	//else
	//{
	//	if(m_Direction == eDirection::RIGHT)
	//		m_Sprite->setSpriteEffect(eSpriteEffect::Horizontally);
	//}
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
{

}