#include "Rambo.h"

Rambo::Rambo()
{

}

Rambo::Rambo(D3DXVECTOR3 _position, eDirection _direction) : Object(_position, _direction)
{
	m_ObjectState = eObjectState::STATE_BILL_IDLE;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BILL_IDLE));
}

void Rambo::Initialize()
{

}

void Rambo::HandleInput()
{
	m_UpdateFlag = 0;
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_DEATH:
		break;
	case STATE_BILL_MOVE_1:
		{
			if(!CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) && !CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_ObjectState = eObjectState::STATE_BILL_IDLE;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}	
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_Sprite->setSpriteEffect(eSpriteEffect::None);
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_Sprite->setSpriteEffect(eSpriteEffect::Horizontally);
			}
			
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
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_ObjectState = eObjectState::STATE_BILL_MOVE_1;
				m_Direction = eDirection::RIGHT;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_ObjectState = eObjectState::STATE_BILL_MOVE_1;
				m_Direction = eDirection::LEFT;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
			
		}
		break;
	case STATE_BILL_JUMP:
		break;
	case STATE_BILL_LIE_DOWN:
		break;
	default:
		break;
	}
}

void Rambo::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_DEATH:
		break;
	case STATE_BILL_MOVE_1:
		{
			if( m_UpdateFlag & (1<<0))
			{
				delete m_Sprite;
				m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BILL_MOVE_1));
			}
			m_Sprite->UpdateAnimation(400);
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
			if( m_UpdateFlag & (1<<0))
			{
				delete m_Sprite;
				m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BILL_IDLE));
			}
		}
		break;
	case STATE_BILL_JUMP:
		break;
	case STATE_BILL_LIE_DOWN:
		break;
	default:
		break;
	}
}

void Rambo::UpdateCollision(Object* checkingObject)
{

}


void Rambo::UpdateMovement()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_DEATH:
		break;
	case STATE_BILL_MOVE_1:
		{
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_Physic->setVelocity(D3DXVECTOR2(1.0f, m_Physic->getVelocity().y));
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_Physic->setVelocity(D3DXVECTOR2(-1.0f, m_Physic->getVelocity().y));
			}
		}
		break;
	case STATE_BILL_MOVE_2:
		break;
	case STATE_BILL_MOVE_3:
		break;
	case STATE_BILL_MOVE_4:
		break;
	case STATE_BILL_IDLE:
		break;
	case STATE_BILL_JUMP:
		break;
	case STATE_BILL_LIE_DOWN:
		break;
	default:
		break;
	}
	this->m_Physic->UpdateMovement(CGameTimeDx9::getInstance());
}


void Rambo::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, m_Physic->getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Physic->getPositionVec3().z);
}


void Rambo::Release()
{

}

Rambo::~Rambo()
{

}