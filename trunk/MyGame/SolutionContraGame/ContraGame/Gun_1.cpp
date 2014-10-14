#include "Gun_1.h"

Gun_1::Gun_1()
{

}

Gun_1::Gun_1(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: Object(_position, _direction, _objectID)
{
	m_Physic = new Physic();
	//m_Physic->setPosition(_position);
	m_Position = _position;
}

void Gun_1::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_GUN_1));
}

void Gun_1::UpdateAnimation()
{
	m_Sprite->UpdateAnimation(300);	
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_DEATH:
		break;
	case STATE_BILL_MOVE_1:
	{
		if (m_UpdateFlag & (1 << 0))
		{
			delete m_Sprite;
			m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BILL_MOVE_1));
			m_UpdateFlag = m_UpdateFlag ^ ( 1 << 0);
		}
		m_Sprite->UpdateAnimation(200);
	}
		break;
	case STATE_BILL_MOVE_2:
		break;
	case STATE_BILL_MOVE_3:
		break;
	case STATE_BILL_MOVE_4:
		break;
	case STATE_BILL_IDLE:
		{
			if (m_UpdateFlag & (1 << 0))
			{
				delete m_Sprite;
				m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BILL_IDLE));
				m_UpdateFlag = 0;
			}
		}
		break;
	case STATE_BILL_JUMP:
		{
			if (m_UpdateFlag & (1 << 0))
			{
				delete m_Sprite;
				m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BILL_JUMP));
				m_UpdateFlag = 0;
			}
			m_Sprite->UpdateAnimation(100);
		}
		break;
	case STATE_BILL_LIE_DOWN:
		break;
	case STATE_SHOOTING:
		{
			if (m_UpdateFlag & (1 << 0))
			{
				delete m_Sprite;
				m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BILL_IDLE));
				m_UpdateFlag = 0;
			}
			m_Sprite->UpdateAnimation(50);
		}
		break;
	default:
		break;
	}
	
}


void Gun_1::UpdateCollision(Object* checkingObject)
{}

void Gun_1:: UpdateMovement()
{}
void Gun_1::Update()
{}
void Gun_1::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}


void Gun_1::Release()
{

}

Gun_1::~Gun_1()
{

}