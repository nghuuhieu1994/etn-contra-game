#include "SpreadGun.h"

SpreadGun::SpreadGun()
{

}

SpreadGun::SpreadGun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void SpreadGun::Initialize()
{
	m_ObjectState = STATE_ALIVE_IDLE;
	m_Position.z = 1.0f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_SPREAD_GUN));
}

void SpreadGun::UpdateAnimation()
{

}


void SpreadGun::UpdateCollision(Object* checkingObject)
{
	if (!isDead)
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
				tempRambo->setSkillBullet(eIDSkillBullet::S_SKILL_BULLET);
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::rambo_1up_sfx)->Play();
			}
							break;
			case eObjectID::TILE_BASE:
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



void SpreadGun:: UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
}

void SpreadGun::Update()
{
	if (m_ObjectState == STATE_DEATH)
	{
		if (isDead)
		{
			Release();
		}
	}
}

void SpreadGun::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void SpreadGun::Release()
{
	isDead = true;
	m_Sprite->Release();
	SAFE_DELETE(m_Sprite);
}

SpreadGun::~SpreadGun()
{

}