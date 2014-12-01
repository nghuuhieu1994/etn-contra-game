#include "WeaponCapsule.h"

WeaponCapsule::WeaponCapsule()
{

}

WeaponCapsule::WeaponCapsule(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, EIDWeaponry	idWeapon)
	: DynamicObject(_position, _direction, _objectID)
{
	m_IDWeaponry = idWeapon;
	m_startPosition = _position;
}

void WeaponCapsule::Initialize()
{
	m_Position.z = 1.0f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_WEAPON_CAPSULE));
	m_deadSprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_ObjectState = STATE_ALIVE_MOVE;
}

void WeaponCapsule::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_MOVE:
		break;
	case STATE_BEFORE_DEATH:
		if (!isDead)
		{
			isDead = true;
			m_Sprite = m_deadSprite;
		}
		m_Sprite->UpdateAnimation(100);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}


void WeaponCapsule::UpdateCollision(Object* checkingObject)
{
	if (!isDead)
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

		if (collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			case BULLET_RAMBO:
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_attacked_sfx)->Play();
				if (m_Sprite->getAnimationAction()->getCurrentIndex() > 3)
				{
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();



					m_ObjectState = STATE_BEFORE_DEATH;
				}
				break;
			default:
				break;
			}

		}
	}
}

float WeaponCapsule::Moving()
{
	return (float)((sin(m_Position.x * 3.14/80.0 ) * 100 + m_startPosition.y) - m_Position.y);
}

void WeaponCapsule:: UpdateMovement()
{
	//
	//m_Physic->setVelocity(D3DXVECTOR2(1.5f, m_Physic->getVelocity().y));
	m_Physic->UpdateMovement(&m_Position);
	m_Physic->setVelocityY((float)((sin(m_Position.x * 3.14/80.0 ) * 100 + m_startPosition.y) - m_Position.y));
	m_Physic->setVelocityX(1.5f);
	
	//Sin(m_Position);
}

void WeaponCapsule::Update()
{

}

void WeaponCapsule::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void WeaponCapsule::Release()
{

}

WeaponCapsule::~WeaponCapsule()
{

}