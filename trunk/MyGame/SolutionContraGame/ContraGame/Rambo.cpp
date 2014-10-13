#include "Rambo.h"

Rambo::Rambo()
{

}

Rambo::Rambo(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID) 
	: Object(_position, _direction, _objectID)
{
	m_Physic = new Physic();
	m_Physic->setPosition(_position);
	m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_IDLE));
	m_Physic->setPosition(D3DXVECTOR3(m_Physic->getPositionVec2().x, m_Physic->getPositionVec2().y, 1.0f));
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
	case eObjectState::STATE_RAMBO_RUN://Run state
		{
			if(!CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) && !CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
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
				m_ObjectState = eObjectState::STATE_RAMBO_SHOOT;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_X))
			{
				m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
				m_Physic->setVelocity(D3DXVECTOR2(m_Physic->getVelocity().x, 5.0f));
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
		}
		break;
	case STATE_RAMBO_SHOOT_RUN:
		{
			if(!CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) && !CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
				m_Physic->setVelocity(D3DXVECTOR2(0, 0));
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_Direction = eDirection::LEFT;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_Direction = eDirection::RIGHT;
			}
			if(!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
			{
				m_ObjectState = eObjectState::STATE_RAMBO_RUN;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
		}
		break;
	case STATE_RAMBO_SHOOT_TOP_RIGHT:
		break;
	case STATE_RAMBO_SHOOT_BOTTOM_RIGHT:
		break;
	case STATE_RAMBO_IDLE:
		{
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_ObjectState = eObjectState::STATE_RAMBO_RUN;
				m_Direction = eDirection::RIGHT;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_ObjectState = eObjectState::STATE_RAMBO_RUN;
				m_Direction = eDirection::LEFT;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
			{
				m_ObjectState = eObjectState::STATE_RAMBO_SHOOT;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_X))
			{
				m_ObjectState = eObjectState::STATE_RAMBO_JUMP;
				m_Physic->setVelocity(D3DXVECTOR2(m_Physic->getVelocity().x, 5.0f));
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
		}
		break;
	case STATE_RAMBO_JUMP:
		{
			
		}
		break;
	case STATE_RAMBO_LIE:
		break;
	case STATE_RAMBO_SHOOT:
		{
			if(!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
			{
				m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
			{
				m_Direction = eDirection::LEFT;
				m_ObjectState = eObjectState::STATE_RAMBO_SHOOT_RUN;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
			}
			if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT))
			{
				m_Direction = eDirection::RIGHT;
				m_ObjectState = eObjectState::STATE_RAMBO_SHOOT_RUN;
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
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
	case STATE_RAMBO_RUN:
	{
		if (m_UpdateFlag & (1 << 0))
		{
			delete m_Sprite;
			m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_RUN));
			m_UpdateFlag = m_UpdateFlag ^ ( 1 << 0);
		}
		m_Sprite->UpdateAnimation(200);
	}
		break;
	case STATE_RAMBO_SHOOT_RUN:
		{
			if (m_UpdateFlag & (1 << 0))
			{
				delete m_Sprite;
				m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SHOOT_RUN));
				m_UpdateFlag = m_UpdateFlag ^ ( 1 << 0);
			}
			m_Sprite->UpdateAnimation(200);
		}
		break;
	case STATE_RAMBO_SHOOT_TOP_RIGHT:
		break;
	case STATE_RAMBO_SHOOT_BOTTOM_RIGHT:
		break;
	case STATE_RAMBO_IDLE:
		{
			if (m_UpdateFlag & (1 << 0))
			{
				delete m_Sprite;
				m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_IDLE));
				m_UpdateFlag = m_UpdateFlag ^ ( 1 << 0);
			}
		}
		break;
	case STATE_RAMBO_JUMP:
		{
			if (m_UpdateFlag & (1 << 0))
			{
				delete m_Sprite;
				m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_JUMP));
				m_UpdateFlag = m_UpdateFlag ^ ( 1 << 0);
			}
			m_Sprite->UpdateAnimation(100);
		}
		break;
	case STATE_RAMBO_LIE:
		break;
	case STATE_RAMBO_SHOOT:
		{
			if (m_UpdateFlag & (1 << 0))
			{
				delete m_Sprite;
				m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_IDLE));
				m_UpdateFlag = m_UpdateFlag ^ ( 1 << 0);
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
	case STATE_RAMBO_RUN:
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
	case STATE_RAMBO_SHOOT_RUN:
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
	case STATE_RAMBO_SHOOT_TOP_RIGHT:
		break;
	case STATE_RAMBO_SHOOT_BOTTOM_RIGHT:
		break;
	case STATE_RAMBO_IDLE:
		break;
	case STATE_RAMBO_JUMP:
		{
			if(m_Physic->getPositionVec2().y < 100)
			{
				m_Physic->setPosition(D3DXVECTOR3(m_Physic->getPositionVec3().x, 100, m_Physic->getPositionVec3().z));
				m_Physic->setVelocity(D3DXVECTOR2(m_Physic->getVelocity().x, 0.0f));
				m_UpdateFlag = m_UpdateFlag | (1 << 0);
				m_ObjectState = eObjectState::STATE_RAMBO_IDLE;
				m_Physic->setVelocity(D3DXVECTOR2(0, 0));
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
	case STATE_RAMBO_LIE:
		break;
	case STATE_RAMBO_SHOOT:
		{
			
		}
		break;
	default:
		break;
	}
	this->m_Physic->UpdateMovement(CGameTimeDx9::getInstance());
}


void Rambo::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Direction == eDirection::RIGHT)
	{
		m_Sprite->Render(spriteHandle,
			m_Physic->getPositionVec2(),
			eSpriteEffect::None, m_Sprite->getRotate(),
			m_Sprite->getScale(),
			m_Physic->getPositionVec3().z);
		return;
	}
	if (m_Direction == eDirection::LEFT)
	{
		m_Sprite->Render(spriteHandle,
			m_Physic->getPositionVec2(),
			eSpriteEffect::Horizontally,
			m_Sprite->getRotate(), m_Sprite->getScale(),
			m_Physic->getPositionVec3().z);
		return;
	}
}

void Rambo::Release()
{

}

Rambo::~Rambo()
{

}