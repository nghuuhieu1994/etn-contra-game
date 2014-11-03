#include "RamboSprite.h"
#include "CInputDx9.h"

RamboSprite::RamboSprite(void)
{
	
	m_moveLeg		= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_MOVE_LEG));
	m_Leg			= m_moveLeg;

	m_Lie			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_LIE));
	m_Run			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_MOVE_BODY));
	m_TopRight		= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SHOOT_TOP_RIGHT_BODY));
	m_BottomRight	= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SHOOT_BOTTOM_RIGHT_BODY));
	m_Shoot			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SHOOT_BODY));
	m_Up			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SHOOT_UP_BODY));
	m_Jump			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_JUMP));
	m_Body = m_Run;
	
	m_inversePositionY = -1;
	timeAnimation = 0;
	m_isJump = false;
	m_isShake = false;
}

void RamboSprite::resetInverseVariable()
{
	m_inversePositionY = -1;
	timeAnimation = 0;
}

void RamboSprite::UpdateAnimation(eObjectState _objectState)
{
	switch (_objectState)
	{
		case STATE_RAMBO_IDLE:
			{
				m_PositionBody	= D3DXVECTOR3(0, 23, 0);
				m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
				m_frameSize		= D3DXVECTOR2(30, 74);
				m_Leg			= m_moveLeg;
				m_Body			= m_Shoot;
				this->Reset();
			}
			break;
		case STATE_RAMBO_JUMP:
			{
				m_PositionBody	= D3DXVECTOR3(0, 0, 0);
				m_frameSize		= D3DXVECTOR2(64, 64);
				m_Leg			= 0;
				m_Body			= m_Jump;
				m_Body->UpdateAnimation(200);
			}
			break;
		case STATE_RAMBO_LIE:
			{
				m_Leg			= 0;
				m_Body			= m_Lie;
				m_frameSize		= D3DXVECTOR2(68, 34);
				m_PositionBody	= D3DXVECTOR3(0, 0, 0);
			}
			break;
		case STATE_RAMBO_RUN:
			{
				m_PositionBody	= D3DXVECTOR3(0, 23, 0);
				m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
				m_frameSize		= D3DXVECTOR2(30, 74);
				m_Leg			= m_moveLeg;
				m_Body			= m_Run;

				m_Leg->UpdateAnimation(250);
				m_Body->getAnimation()->UpdateAnimationInverse(300);
			}
			break;
		case STATE_RAMBO_SHOOT:
			break;
		case STATE_RAMBO_AIM_BOTTOM_RIGHT:
			{
				m_PositionBody	= D3DXVECTOR3(0, 23, 0);
				m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
				m_frameSize		= D3DXVECTOR2(30, 74);
				m_Leg			= m_moveLeg;
				m_Body			= m_BottomRight;

				m_Leg->UpdateAnimation(250);
			}
			break;
		case STATE_RAMBO_SHOOT_RUN:
			{
				m_PositionBody	= D3DXVECTOR3(0, 23, 0);
				m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
				m_frameSize		= D3DXVECTOR2(30, 74);
				m_Leg			= m_moveLeg;
				m_Body			= m_Shoot;
				m_Leg->UpdateAnimation(250);
			}
			break;
		case STATE_RAMBO_AIM_TOP_RIGHT:
			{
				m_PositionBody	= D3DXVECTOR3(0, 23, 0);
				m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
				m_frameSize		= D3DXVECTOR2(30, 74);
				m_Leg			= m_moveLeg;
				m_Body			= m_TopRight;
				m_Leg->UpdateAnimation(250);
			}
			break;
		case STATE_RAMBO_AIM_UP:
			{
				m_PositionBody	= D3DXVECTOR3(0, 23, 0);
				m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
				m_frameSize		= D3DXVECTOR2(30, 74);
				m_Leg			= m_moveLeg;
				m_Body			= m_Up;

				this->Reset();
			}
			break;
		case STATE_RAMBO_FALL:
			{
				m_PositionBody	= D3DXVECTOR3(0, 23, 0);
				m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
				m_frameSize		= D3DXVECTOR2(30, 74);
				m_Leg			= m_moveLeg;
				m_Body			= m_Run;

				m_Body->getAnimation()->setSourceRectAtIndex(0);
				m_Leg->getAnimation()->setSourceRectAtIndex(1);
			}
			break;
		case STATE_SHOOTING:
			break;
		default:
			break;
	}
	//if(m_isJump)
	//{
	//	m_Body = m_Jump;
	//	m_Leg = 0;
	//	m_PositionBody.y = 0;
	//	m_frameSize = D3DXVECTOR2(64, 64);
	//	m_Body->UpdateAnimation(150);
	//	return;
	//}
	//else
	//{
	//	m_Body = m_Shoot;
	//	m_Leg = m_moveLeg;
	//	m_frameSize = D3DXVECTOR2(30, 74);
	//	m_PositionBody = D3DXVECTOR3(0, 23, 0);
	//}

	//if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) || CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
	//{
	//	m_Leg->getAnimation()->UpdateAnimation(250);
	//	if(CInputDx9::getInstance()->IsKeyDown(DIK_UP))
	//	{
	//		m_Body = m_TopRight;
	//		if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
	//		{
	//			this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	//			if(this->timeAnimation > 100)
	//			{
	//				m_PositionBody.y += 2 * m_inversePositionY;
	//				m_inversePositionY *= -1;
	//				timeAnimation = 0;
	//			}
	//		}
	//		else
	//		{
	//			m_inversePositionY = -1;
	//			m_PositionBody.y = 23;
	//			timeAnimation = 0;
	//		}
	//	}
	//	else
	//	{
	//		if(CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
	//		{
	//			m_Body = m_BottomRight;
	//			if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
	//			{
	//				this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	//				if(this->timeAnimation > 100)
	//				{
	//					m_PositionBody.y += 2 * m_inversePositionY;
	//					m_inversePositionY *= -1;
	//					timeAnimation = 0;
	//				}
	//			}
	//			else
	//			{
	//				m_inversePositionY = -1;
	//				m_PositionBody.y = 23;
	//				timeAnimation = 0;
	//			}
	//		}
	//		else
	//		{
	//			if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
	//			{
	//				m_Body = m_Shoot;
	//				this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	//				if(this->timeAnimation > 100)
	//				{
	//					m_PositionBody.y += 2 * m_inversePositionY;
	//					m_inversePositionY *= -1;
	//					timeAnimation = 0;
	//				}
	//			}
	//			else
	//			{
	//				m_inversePositionY = -1;
	//				m_PositionBody.y = 23;
	//				timeAnimation = 0;
	//				m_Body = m_Run;
	//				m_Body->getAnimation()->UpdateAnimationInverse(250); 
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	m_Body = m_Shoot;
	//	if(CInputDx9::getInstance()->IsKeyDown(DIK_UP))
	//	{
	//		m_Body = m_Up;
	//	}
	//	if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
	//	{
	//		this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	//		if(this->timeAnimation > 100)
	//		{
	//			m_PositionBody.y += 2 * m_inversePositionY;
	//			m_inversePositionY *= -1;
	//			timeAnimation = 0;
	//		}
	//	}
	//	else
	//	{
	//		m_inversePositionY = -1;
	//		m_PositionBody.y = 23;
	//		timeAnimation = 0;
	//		m_Body->getAnimation()->UpdateAnimationInverse(250); 
	//	}
	//	m_Body->getAnimation()->Reset();
	//	m_Leg->getAnimation()->Reset();
	//}
	////code nay de lam cai hieu ung giat giat khi ban dan
	////this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	////if(this->timeAnimation > 100)
	////{
	////	m_PositionBody.y += 2 * m_inversePositionY;
	////	m_inversePositionY *= -1;
	////	timeAnimation = 0;
	////}
}

void RamboSprite::saveCurrentState()
{
	m_tempPositionBody = m_PositionBody;
	m_tempPositionLeg = m_PositionLeg;
}

void RamboSprite::loadCurrentState()
{
	m_PositionBody = m_tempPositionBody;
	m_PositionLeg = m_tempPositionLeg;
}

void RamboSprite::shakeYourBodyBitch()
{
	m_isShake = true;
}

void RamboSprite::Reset()
{
	if (m_Body != 0)
	{
		m_Body->getAnimation()->Reset(); 
	}
	if (m_Leg != 0)
	{
		m_Leg->getAnimation()->Reset(); 
	}
}

void RamboSprite::Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep)
{
	if (m_isShake)
	{
		this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(this->timeAnimation > 150)
		{
			m_PositionBody.y += 2 * m_inversePositionY;
			m_inversePositionY *= -1;
			timeAnimation = 0;
			m_isShake = false;
		}
	}
	if (m_Leg != 0)
	{
		m_Leg->Render(spriteHandle, D3DXVECTOR2(position.x, position.y + m_PositionLeg.y), effect, rotateAngle, scale, deep); 
	}

	if (m_Body != 0)
	{
		m_Body->Render(spriteHandle, D3DXVECTOR2(position.x, position.y + m_PositionBody.y), effect, rotateAngle, scale, deep); 
	}
}

RamboSprite::~RamboSprite(void)
{
}
