#include "WeaponSensor.h"

WeaponSensor::WeaponSensor()
{

}

WeaponSensor::WeaponSensor(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID, EIDWeaponry idWeaponry) 
	: DynamicObject(_position, _direction, _objectID)
{
	m_IDWeapon = idWeaponry;
}

void WeaponSensor::Initialize()
{
	m_Position.z = 1.0f;
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_alive = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_WEAPON_SENSOR));
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = sprite_alive;
}

void WeaponSensor::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE: 
		if(abs(CGlobal::Rambo_X - this->getPositionVec2().x) > 200)
		{
			 this->getSprite()->getAnimation()->setCurrentFrame(0);
		}
		else
		{
			 this->getSprite()->getAnimation()->setIndexStart(0);
			 this->getSprite()->getAnimation()->setIndexEnd(6);
			 m_Sprite->UpdateAnimation(500);
		}
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


void WeaponSensor::UpdateCollision(Object* checkingObject)
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

					if (m_IDWeapon == EIDWeaponry::BARRIER)
					{
						WeaponryManager::getInstance()->AddElement(new Barrier(m_Position, eDirection::RIGHT, eObjectID::OBJECT_BARRIER));
					}
					if (m_IDWeapon == EIDWeaponry::FLAME_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new FlameGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_FLAME_GUN));
					}
					if (m_IDWeapon == EIDWeaponry::LASER_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new LaserGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_LASER_GUN));
					}
					if (m_IDWeapon == EIDWeaponry::MACHINE_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new MachineGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_MACHINE_GUN));
					}
					if (m_IDWeapon == EIDWeaponry::RAPID_FIRE)
					{
						WeaponryManager::getInstance()->AddElement(new RapidFire(m_Position, eDirection::RIGHT, eObjectID::OBJECT_RAPID_GUN));
					}
					if (m_IDWeapon == EIDWeaponry::SPREAD_GUN)
					{
						WeaponryManager::getInstance()->AddElement(new SpreadGun(m_Position, eDirection::RIGHT, eObjectID::OBJECT_SPREAD_GUN));
					}
				}
				checkingObject->setObjectState(STATE_DEATH);
				break;
			default:
				break;
			}
		}
	}
}

void WeaponSensor::UpdateMovement()
{}
void WeaponSensor::Update()
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
void WeaponSensor::Render(SPRITEHANDLE spriteHandle)
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


void WeaponSensor::Release()
{
	m_Sprite = 0;
	sprite_alive->Release();
	sprite_dead->Release();
	SAFE_DELETE(sprite_alive);
	SAFE_DELETE(sprite_dead);
}

WeaponSensor::~WeaponSensor()
{

}