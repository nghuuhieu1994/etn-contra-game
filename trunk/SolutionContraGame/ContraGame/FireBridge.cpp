#include "FireBridge.h"

FireBridge::FireBridge()
{
}

FireBridge::FireBridge(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
}

void FireBridge::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	m_Direction = eDirection::RIGHT;
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_FIRE_BRIDGE));
	m_Sprite = sprite_main;
	m_TimeChangeState = 0;
	m_Position.z = 1.0f;
	
	m_fire_1 = new Fire(D3DXVECTOR3(m_Position.x - 5, m_Position.y + 10, 1), eDirection::RIGHT, eObjectID::FIRE);
	m_fire_2 = new Fire(D3DXVECTOR3(m_Position.x + 5, m_Position.y + 10, 1), eDirection::LEFT, eObjectID::FIRE);
	m_fire_1->Initialize();
	m_fire_2->Initialize();

	m_fire_1->getPhysic()->setVelocityX(m_fire_2->getPhysic()->getVelocity().x * -1);	
}

void FireBridge::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Sprite->getAnimation()->setCurrentFrame(0);
		if(m_fire_1 != NULL && m_fire_2 != NULL )
		{
			m_fire_1->UpdateAnimation();
			m_fire_2->UpdateAnimation();
		}
		//m_Sprite->UpdateAnimation(1000);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}

void FireBridge::UpdateCollision(Object* checkingObject)
{
	if(!isDead) 
	{
		if(checkingObject->getID() == eObjectID::RAMBO)
		{
			//IDDirection collideDirection = this->m_Collision->CheckCollision(this, checkingObject);

			//if(collideDirection != IDDirection::DIR_NONE)
			//{

			//}
			m_fire_1->UpdateCollision(checkingObject);
			m_fire_2->UpdateCollision(checkingObject);
		}
	}
}

void FireBridge::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		if(m_fire_1 != NULL &&  m_fire_2 != NULL)
		{
			m_fire_1->UpdateMovement();
			m_fire_2->UpdateMovement();
		}
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void FireBridge::Update()
{	
}

void FireBridge::Render(SPRITEHANDLE spriteHandle)
{
	m_distanceY = (int)(m_Position.y - CGlobal::Rambo_Y);
	if(m_Sprite != 0 )
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
		if(m_fire_1 != NULL && m_fire_2  != NULL  && m_distanceY <= 100)
		{
			m_fire_1->Render(spriteHandle);
			m_fire_2->Render(spriteHandle);
		}
	}
}

void FireBridge::Release()
{
	m_Sprite = 0;
	sprite_main->Release();
	SAFE_DELETE(sprite_main);
	m_fire_1->Release();
	m_fire_2->Release();
}

FireBridge::~FireBridge()
{
}