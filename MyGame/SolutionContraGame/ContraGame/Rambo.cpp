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
				m_Physic->setVelocity(D3DXVECTOR2(0, 0));
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_Direction = eDirection::RIGHT;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_Direction = eDirection::LEFT;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
			{
				m_ObjectState = eObjectState::STATE_SHOOTING;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_X))
			{
				m_ObjectState = eObjectState::STATE_BILL_JUMP;
				m_Physic->setVelocity(D3DXVECTOR2(m_Physic->getVelocity().x, 5.0f));
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
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
			if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
			{
				m_ObjectState = eObjectState::STATE_SHOOTING;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_X))
			{
				m_ObjectState = eObjectState::STATE_BILL_JUMP;
				m_Physic->setVelocity(D3DXVECTOR2(m_Physic->getVelocity().x, 5.0f));
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
		}
		break;
	case STATE_BILL_JUMP:
		{
			
		}
		break;
	case STATE_BILL_LIE_DOWN:
		break;
	case STATE_SHOOTING:
		{
			if(!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
			{
				m_ObjectState = eObjectState::STATE_BILL_IDLE;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_Direction = eDirection::LEFT;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_Direction = eDirection::RIGHT;
			}
		}
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
		if (m_UpdateFlag & (1 << 0))
		{
			delete m_Sprite;
			m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BILL_MOVE_1));
			m_UpdateFlag = 0;
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
				m_Physic->setVelocity(D3DXVECTOR2(1.5f, m_Physic->getVelocity().y));
				break;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_Physic->setVelocity(D3DXVECTOR2(-1.5f, m_Physic->getVelocity().y));
				break;
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
		{
			if(m_Physic->getPositionVec2().y < 100)
			{
				m_Physic->setPosition(D3DXVECTOR3(m_Physic->getPositionVec3().x, 100, m_Physic->getPositionVec3().z));
				m_Physic->setVelocity(D3DXVECTOR2(m_Physic->getVelocity().x, 0.0f));
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
				m_ObjectState = eObjectState::STATE_BILL_IDLE;
				return;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_Physic->setVelocity(D3DXVECTOR2(1.5f, m_Physic->getVelocity().y));
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_Physic->setVelocity(D3DXVECTOR2(-1.5f, m_Physic->getVelocity().y));
			}
			m_Physic->setVelocity(D3DXVECTOR2(m_Physic->getVelocity().x, m_Physic->getVelocity().y - 0.1f));
		}
		break;
	case STATE_BILL_LIE_DOWN:
		break;
	case STATE_SHOOTING:
		{
			m_Physic->setVelocity(D3DXVECTOR2(0, m_Physic->getVelocity().y));
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_Physic->setVelocity(D3DXVECTOR2(1.5f, m_Physic->getVelocity().y));
				break;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_Physic->setVelocity(D3DXVECTOR2(-1.5f, m_Physic->getVelocity().y));
				break;
			}
		}
		break;
	default:
		break;
	}
	this->m_Physic->UpdateMovement(CGameTimeDx9::getInstance());
	//CGlobal::RamboPosition = m_Physic->getPositionVec2();
}


void Rambo::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Direction == eDirection::RIGHT)
	{
		m_Sprite->Render(spriteHandle, m_Physic->getPositionVec2(), eSpriteEffect::None, m_Sprite->getRotate(), m_Sprite->getScale(), m_Physic->getPositionVec3().z);
		return;
	}
	if (m_Direction == eDirection::LEFT)
	{
		m_Sprite->Render(spriteHandle, m_Physic->getPositionVec2(), eSpriteEffect::Horizontally, m_Sprite->getRotate(), m_Sprite->getScale(), m_Physic->getPositionVec3().z);
		return;
	}
}

void Rambo::Release()
{

}

Rambo::~Rambo()
{

}