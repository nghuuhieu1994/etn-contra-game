#include "RapidFire.h"

RapidFire::RapidFire()
{

}

RapidFire::RapidFire(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void RapidFire::Initialize()
{
	m_ObjectState == STATE_ALIVE_IDLE;
	m_Position.z = 1.0f;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAPID_FIRE));
}

void RapidFire::UpdateAnimation()
{

}


void RapidFire::UpdateCollision(Object* checkingObject)
{
	if (!isDead)
	{
		IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);
		if (collideDirection != IDDirection::DIR_NONE)
		{
			switch (checkingObject->getID())
			{
			case eObjectID::RAMBO:
				isDead = true;
				this->m_ObjectState = STATE_DEATH;
				SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::BROKEN)->Play();
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



void RapidFire:: UpdateMovement()
{
	m_Physic->UpdateMovement(&m_Position);
}

void RapidFire::Update()
{
	if (m_ObjectState == STATE_DEATH)
	{
		if (isDead)
		{
			Release();
		}
	}
}

void RapidFire::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void RapidFire::Release()
{
	isDead = true;
	m_Sprite->Release();
	SAFE_DELETE(m_Sprite);
}

RapidFire::~RapidFire()
{

}