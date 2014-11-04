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

	m_Swim			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SWIM));
	m_Dive			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_DIVE));
	m_WaterBomb		= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_WATER_BOMB));
	m_Climb			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_CLIMB));

	m_Body = m_Run;
	
	m_inversePositionY = -1;
	m_timeShakeAnimation = 0;
	m_isJump = false;
	m_isShake = false;
	//m_PositionBody	= D3DXVECTOR3(0, 23, 0);
	m_previousState = (eObjectState)-1;
}

void RamboSprite::resetInverseVariable()
{
	m_inversePositionY = -1;
	m_timeShakeAnimation = 0;
}

void RamboSprite::UpdateAnimation(eObjectState _objectState)
{
	switch (_objectState)
	{
		case STATE_RAMBO_IDLE:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
					m_frameSize		= D3DXVECTOR2(30, 74);
					m_Leg			= m_moveLeg;
					m_Body			= m_Shoot;

					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}
				if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}
				this->Reset();
			}
			break;
		case STATE_RAMBO_JUMP:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 0, 0);
					m_frameSize		= D3DXVECTOR2(64, 64);
					m_Leg			= 0;
					m_Body			= m_Jump; 
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}
				m_Body->UpdateAnimation(200);
			}
			break;
		case STATE_RAMBO_LIE:
			{
				if (m_previousState != _objectState)
				{
					m_Leg			= 0;
					m_Body			= m_Lie;
					m_frameSize		= D3DXVECTOR2(68, 34);
					m_PositionBody	= D3DXVECTOR3(0, 0, 0); 
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}

				if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 0, 0);
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}
			}
			break;
		case STATE_RAMBO_RUN:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
					m_frameSize		= D3DXVECTOR2(30, 74);
					m_Leg			= m_moveLeg;
					m_Body			= m_Run;
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}

				m_Leg->UpdateAnimation(250);
				m_Body->getAnimation()->UpdateAnimationInverse(300);
			}
			break;
		case STATE_RAMBO_SHOOT:
			break;
		case STATE_RAMBO_AIM_BOTTOM_RIGHT:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 22, 0);
					m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
					m_frameSize		= D3DXVECTOR2(30, 74);
					m_Leg			= m_moveLeg;
					m_Body			= m_BottomRight;
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}

				if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 22, 0);
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}
				m_Leg->UpdateAnimation(250);
			}
			break;
		case STATE_RAMBO_SHOOT_RUN:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
					m_frameSize		= D3DXVECTOR2(30, 74);
					m_Leg			= m_moveLeg;
					m_Body			= m_Shoot; 
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}

				if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}
				m_Leg->UpdateAnimation(250);
			}
			break;
		case STATE_RAMBO_AIM_TOP_RIGHT:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
					m_frameSize		= D3DXVECTOR2(30, 74);
					m_Leg			= m_moveLeg;
					m_Body			= m_TopRight; 
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}

				if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}
				m_Leg->UpdateAnimation(250);
			}
			break;
		case STATE_RAMBO_AIM_UP:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
					m_frameSize		= D3DXVECTOR2(30, 74);
					m_Leg			= m_moveLeg;
					m_Body			= m_Up;
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}

				if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}
				this->Reset();
			}
			break;
		case STATE_RAMBO_FALL:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					m_PositionLeg	= D3DXVECTOR3(0, -5, 0);
					m_frameSize		= D3DXVECTOR2(30, 74);
					m_Leg			= m_moveLeg;
					m_Body			= m_Run;
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}

				m_Body->getAnimation()->setSourceRectAtIndex(0);
				m_Leg->getAnimation()->setSourceRectAtIndex(1);
			}
			break;
		case STATE_RAMBO_WATER_BOMB:
			{

			}
			break;
		case STATE_RAMBO_DIVE:
			{

			}
			break;
		case STATE_RAMBO_SWIM_SHOOT:
			{

			}
			break;
		case STATE_RAMBO_SWIM:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 0, 0);
					
					m_frameSize		= D3DXVECTOR2(64, 64);
					m_Leg			= 0;
					m_Body			= m_Swim;
					m_inversePositionY = -1;
					m_timeShakeAnimation = 0;
				}

				shakeBody();
			}
			break;
		case STATE_RAMBO_CLIMB:
			{

			}
			break;
		case STATE_SHOOTING:
			break;
		default:
			break;
	}
	m_previousState = _objectState;
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

void RamboSprite::shakeBody()
{
	this->m_timeShakeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if(this->m_timeShakeAnimation > 150)
	{
		m_PositionBody.y += 2 * m_inversePositionY;
		
		m_inversePositionY *= -1;
		m_timeShakeAnimation = 0;
	}
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
