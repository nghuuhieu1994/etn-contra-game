#include "LaserGun.h"

LaserGun::LaserGun()
{

}

LaserGun::LaserGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void LaserGun::Initialize()
{
	m_ObjectState = STATE_ALIVE_IDLE;
	m_Position.z = 1.0f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_LASER_GUN));
}

void LaserGun::UpdateAnimation()
{

}


void LaserGun::UpdateCollision(Object* checkingObject)
{
	if (!isDead && checkingObject->getID() != eObjectID::ENEMY_RUN)
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
		if (collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			case eObjectID::RAMBO:
			{
				isDead = true;
				this->m_ObjectState = STATE_DEATH;
			    Rambo* tempRambo = (Rambo*) checkingObject;
				tempRambo->setSkillBullet(eIDSkillBullet::L_SKILL_BULLET);
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::rambo_1up_sfx)->Play();
			}
				break;
			case eObjectID::TILE_BASE:
			case eObjectID::BRIDGE:
				if (collideDirection == IDDirection::DIR_TOP)
				{
					if (getPhysic()->getVelocity().y <= 0)
					{
						getPhysic()->setVelocity(D3DXVECTOR2(0.0f, 0.0f));
					}
				}
				break;
			default:
				break;
			}

		}
	}
}



void LaserGun:: UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);	
}

void LaserGun::Update()
{
	if (m_ObjectState == STATE_DEATH)
	{
		if (isDead)
		{
			Release();
		}
	}
}

void LaserGun::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void LaserGun::Release()
{
	isDead = true;
	m_Sprite->Release();
	SAFE_DELETE(m_Sprite);
}

LaserGun::~LaserGun()
{

}