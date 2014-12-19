#include "WeaponCapsuleVer2.h"

WeaponCapsuleVer2::WeaponCapsuleVer2()
{

}

WeaponCapsuleVer2::WeaponCapsuleVer2(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, eObjectID	idWeapon)
	: DynamicObject(_position, _direction, _objectID)
{
	m_IDWeaponry = idWeapon;
}

void WeaponCapsuleVer2::Initialize()
{
	m_Position.z = 1.0f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_WEAPON_CAPSULE));
	m_deadSprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Physic->setVelocity(D3DXVECTOR2(1.0f, 2.0f));
	m_Physic->setAccelerate(D3DXVECTOR2(0.0f, 0.08f));
	m_ObjectState = STATE_ALIVE_MOVE;
}

void WeaponCapsuleVer2::UpdateAnimation()
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


void WeaponCapsuleVer2::UpdateCollision(Object* checkingObject)
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
				//if (m_Sprite->getAnimationAction()->getCurrentIndex() > 3)
				{
					SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::enemy_dead_sfx)->Play();
					m_ObjectState = STATE_BEFORE_DEATH;
#pragma region AddWeaponry
					if (m_IDWeaponry == eObjectID::OBJECT_BARRIER)
					{
						WeaponryManager::getInstance()->AddElement(new Barrier(m_Position, eDirection::RIGHT, eObjectID::OBJECT_BARRIER));
					}
					if (m_IDWeaponry == eObjectID::OBJECT_FLAME_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new FlameGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_FLAME_GUN));
					}
					if (m_IDWeaponry  == eObjectID::OBJECT_LASER_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new LaserGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_LASER_GUN));
					}
					if (m_IDWeaponry == eObjectID::OBJECT_MACHINE_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new MachineGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_MACHINE_GUN));
					}
					if (m_IDWeaponry == eObjectID::OBJECT_RAPID_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new RapidFire(m_Position, eDirection::RIGHT, eObjectID::OBJECT_RAPID_GUN));
					}
					if (m_IDWeaponry == eObjectID::OBJECT_SPREAD_GUN)
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


void WeaponCapsuleVer2::UpdateMovement()
{
	if (m_Physic->getVelocity().x <= -2.0f || m_Physic->getVelocity().x >= 2.0f )
	{
		m_Physic->setAccelerateX(m_Physic->getAccelerate().x * -1);
	}
	m_Physic->UpdateMovement(&m_Position);
}

void WeaponCapsuleVer2::Update()
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

void WeaponCapsuleVer2::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void WeaponCapsuleVer2::Release()
{
	m_Sprite->Release();
	m_deadSprite->Release();
	SAFE_DELETE(m_Sprite);
	SAFE_DELETE(m_deadSprite);
}

WeaponCapsuleVer2::~WeaponCapsuleVer2()
{

}