#include "MachineGun.h"

MachineGun::MachineGun()
{

}

MachineGun::MachineGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void MachineGun::Initialize()
{
	m_ObjectState = STATE_ALIVE_IDLE;
	m_Position.z = 1.0f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_MACHINE_GUN));
}

void MachineGun::UpdateAnimation()
{

}

void MachineGun::UpdateCollision(Object* checkingObject)
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
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::rambo_1up_sfx)->Play();
				Rambo* tempRambo = (Rambo*) checkingObject;
				tempRambo->setSkillBullet(eIDSkillBullet::M_SKILL_BULLET);
				isDead = true;
				this->m_ObjectState = STATE_DEATH;
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


void MachineGun:: UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
}

void MachineGun::Update()
{
	if (m_ObjectState == STATE_DEATH)
	{
		if (isDead)
		{
			Release();
		}
	}
}

void MachineGun::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void MachineGun::Release()
{
	isDead = true;
	m_Sprite->Release();
	SAFE_DELETE(m_Sprite);
}

MachineGun::~MachineGun()
{

}