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
	m_Dead			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_BEFORE_DEAD));
	m_Swim			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SWIM));
	m_Dive			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_DIVE));
	m_WaterBomb		= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_WATER_BOMB));
	m_Climb			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_CLIMB));

	m_Body = m_Run;
	
	
	m_isJump = false;
	m_isShake = false;
	//m_PositionBody	= D3DXVECTOR3(0, 23, 0);
	m_previousState = (eObjectState)-1;
	m_timesShake = 0;
	resetInverseVariable();
}

void RamboSprite::resetInverseVariable()
{
	m_inversePositionY = -1;
	m_timeShakeAnimation = 0;
	if (m_timesShake % 2 != 0)
	{
		m_timesShake = 0;
	}
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

					resetInverseVariable();
				}
				/*if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					resetInverseVariable();
				}*/
				this->Reset();
				this->shakeBody();
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
					resetInverseVariable();
				}
				m_Body->UpdateAnimation(150);
				this->shakeBody();
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
					resetInverseVariable();
				}
				this->shakeBody();
				/*if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 0, 0);
					resetInverseVariable();
				}*/
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
					resetInverseVariable();
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
					resetInverseVariable();
				}

				/*if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 22, 0);
					resetInverseVariable();
				}*/
				m_Leg->UpdateAnimation(250);
				this->shakeBody();
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
					resetInverseVariable();
				}

				/*if (!CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_PositionBody	= D3DXVECTOR3(0, 23, 0);
					resetInverseVariable();
				}*/
				m_Leg->UpdateAnimation(250);
				this->shakeBody();
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
					resetInverseVariable();
				}

				m_Leg->UpdateAnimation(250);
				this->shakeBody();
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
					resetInverseVariable();
				}

				this->shakeBody();
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
					resetInverseVariable();
				}

				m_Body->getAnimation()->setSourceRectAtIndex(0);
				m_Leg->getAnimation()->setSourceRectAtIndex(1);
			}
			break;
		case STATE_RAMBO_WATER_BOMB:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, -8, 0);
					m_frameSize		= D3DXVECTOR2(32, 32);
					m_Leg			= 0;
					m_Body			= m_WaterBomb;
					resetInverseVariable();
				}
			}
			break;
		case STATE_RAMBO_BEFORE_DEAD:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 0, 0);
					m_frameSize		= D3DXVECTOR2(68, 12);
					m_Leg			= 0;
					m_Body			= m_Dead;
					resetInverseVariable();
					m_Body->getAnimation()->setCurrentFrame(0);
				}
				if (m_Body->getAnimation()->getCurrentIndex() != m_Body->getAnimation()->getEndIndex())
				{
					m_Body->UpdateAnimation(250); 
				}
			}
			break;
		case STATE_RAMBO_DEAD:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 0, 0);
					m_frameSize		= D3DXVECTOR2(68, 12);
					m_Leg			= 0;
					m_Body			= m_Dead;
					resetInverseVariable();
				}
				m_Body->getAnimation()->setSourceRectAtIndex(4);
			}
			break;
		case STATE_RAMBO_DIVE:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 0, 0);
					
					m_frameSize		= D3DXVECTOR2(32, 32);
					m_Leg			= 0;
					m_Body			= m_Dive;
					resetInverseVariable();
				}

				shakeBodySwim();
			}
			break;
		case STATE_RAMBO_SWIM_SHOOT:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 12, 0);
					m_PositionLeg	= D3DXVECTOR3(0, 0, 0);

					m_frameSize		= D3DXVECTOR2(32, 32);
					m_Leg			= m_Dive;
					m_Body			= m_Shoot;
					resetInverseVariable();
				}
				this->shakeBody();
			}
			break;
		case STATE_RAMBO_SWIM_SHOOT_UP:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 12, 0);
					m_PositionLeg	= D3DXVECTOR3(0, 0, 0);

					m_frameSize		= D3DXVECTOR2(32, 32);
					m_Leg			= m_Dive;
					m_Body			= m_Up;
					resetInverseVariable();
				}
				this->shakeBody();
				
			}
			break;
		case STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 12, 0);
					m_PositionLeg	= D3DXVECTOR3(0, 0, 0);
					
					m_frameSize		= D3DXVECTOR2(32, 32);
					m_Leg			= m_Dive;
					m_Body			= m_TopRight;
					resetInverseVariable();
				}
				this->shakeBody();
				
			}
			break;
		case STATE_RAMBO_SWIM:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 0, 0);
					
					m_frameSize		= D3DXVECTOR2(32, 32);
					m_Leg			= 0;
					m_Body			= m_Swim;
					resetInverseVariable();
				}

				shakeBodySwim();
			}
			break;
		case STATE_RAMBO_CLIMB:
			{
				if (m_previousState != _objectState)
				{
					m_PositionBody	= D3DXVECTOR3(0, 0, 0);
					
					m_frameSize		= D3DXVECTOR2(20, 20);
					m_Leg			= 0;
					m_Body			= m_Climb;
					resetInverseVariable();
				}
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
	if (m_timesShake > 0)
	{
		this->m_timeShakeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if(this->m_timeShakeAnimation > 150)
		{
			m_PositionBody.y += 2 * m_inversePositionY;

			m_inversePositionY *= -1;
			m_timeShakeAnimation = 0;
			--m_timesShake;
		} 
	}
}

void RamboSprite::shakeBodySwim()
{
	this->m_timeShakeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if(this->m_timeShakeAnimation > 500)
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

void RamboSprite::Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep, D3DXCOLOR color)
{
	if (m_Leg != 0)
	{
		m_Leg->Render(spriteHandle, D3DXVECTOR2(position.x, position.y + m_PositionLeg.y), effect, rotateAngle, scale, deep, color); 
	}

	if (m_Body != 0)
	{
		m_Body->Render(spriteHandle, D3DXVECTOR2(position.x, position.y + m_PositionBody.y), effect, rotateAngle, scale, deep, color); 
	}
}

RamboSprite::~RamboSprite(void)
{
}
