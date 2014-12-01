#include "WeaponCapsule.h"

WeaponCapsule::WeaponCapsule()
{

}

WeaponCapsule::WeaponCapsule(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, EIDWeaponry	idWeapon)
	: DynamicObject(_position, _direction, _objectID)
{
	m_IDWeaponry = idWeapon;
}

void WeaponCapsule::Initialize()
{
	m_Position.z = 1.0f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_WEAPON_CAPSULE));
	m_deadSprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Physic->setVelocity(D3DXVECTOR2(1.0, 1.0));
	m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.03f));
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
#pragma region AddWeaponry
					if (m_IDWeaponry == EIDWeaponry::BARRIER)
					{
						WeaponryManager::getInstance()->AddElement(new Barrier(m_Position, eDirection::RIGHT, eObjectID::OBJECT_BARRIER));
					}
					if (m_IDWeaponry == EIDWeaponry::FLAME_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new FlameGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_FLAME_GUN));
					}
					if (m_IDWeaponry  == EIDWeaponry::LASER_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new LaserGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_LASER_GUN));
					}
					if (m_IDWeaponry == EIDWeaponry::MACHINE_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new MachineGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_MACHINE_GUN));
					}
					if (m_IDWeaponry == EIDWeaponry::RAPID_FIRE)
					{
						WeaponryManager::getInstance()->AddElement(new RapidFire(m_Position, eDirection::RIGHT, eObjectID::OBJECT_RAPID_GUN));
					}
					if (m_IDWeaponry == EIDWeaponry::SPREAD_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new SpreadGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_SPREAD_GUN));
					}
#pragma endregion AddWeaponry
				}
				break;
			default:
				break;
			}
		}
	}
}


void WeaponCapsule:: UpdateMovement()
{
	if (m_Physic->getVelocity().y <= -1.0f || m_Physic->getVelocity().y >= 1.0f )
	{
		m_Physic->setAccelerateY(m_Physic->getAccelerate().y * -1);
	}
	m_Physic->UpdateMovement(&m_Position);
}

void WeaponCapsule::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_BEFORE_DEATH:
		if (isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 1000)
			{
				m_TimeChangeState = 0;
				m_ObjectState = eObjectState::STATE_DEATH;
			}
		}
		break;
	case STATE_DEATH:
		this->Release();
		break;
	default:
		break;
	}
}

void WeaponCapsule::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void WeaponCapsule::Release()
{
	m_Sprite->Release();
	m_deadSprite->Release();
	SAFE_DELETE(m_Sprite);
	SAFE_DELETE(m_deadSprite);
}

WeaponCapsule::~WeaponCapsule()
{

}