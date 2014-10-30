#include "RamboSprite.h"
#include "CInputDx9.h"

RamboSprite::RamboSprite(void)
{
	
	m_Leg			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_MOVE_LEG));
	m_Run			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_MOVE_BODY));
	m_TopRight		= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SHOOT_TOP_RIGHT_BODY));
	m_BottomRight	= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SHOOT_BOTTOM_RIGHT_BODY));
	m_Shoot			= new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_SHOOT_BODY));
	m_Body = m_Run;
	m_PositionBody = D3DXVECTOR3(0, 18, 0);
	m_PositionLeg = D3DXVECTOR3(0, -10, 0);
	m_inversePositionY = -1;
	timeAnimation = 0;
}

void RamboSprite::UpdateAnimation()
{
	if(CInputDx9::getInstance()->IsKeyDown(DIK_RIGHT) || CInputDx9::getInstance()->IsKeyDown(DIK_LEFT))
	{
		m_Leg->getAnimation()->UpdateAnimation(250);
		if(CInputDx9::getInstance()->IsKeyDown(DIK_UP))
		{
			m_Body = m_TopRight;
			if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
			{
				this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
				if(this->timeAnimation > 100)
				{
					m_PositionBody.y += 2 * m_inversePositionY;
					m_inversePositionY *= -1;
					timeAnimation = 0;
				}
			}
			else
			{
				m_inversePositionY = -1;
				m_PositionBody.y = 18;
				timeAnimation = 0;
			}
		}
		else
		{
			if(CInputDx9::getInstance()->IsKeyDown(DIK_DOWN))
			{
				m_Body = m_BottomRight;
				if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
					if(this->timeAnimation > 100)
					{
						m_PositionBody.y += 2 * m_inversePositionY;
						m_inversePositionY *= -1;
						timeAnimation = 0;
					}
				}
				else
				{
					m_inversePositionY = -1;
					m_PositionBody.y = 18;
					timeAnimation = 0;
				}
			}
			else
			{
				if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
				{
					m_Body = m_Shoot;
					this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
					if(this->timeAnimation > 100)
					{
						m_PositionBody.y += 2 * m_inversePositionY;
						m_inversePositionY *= -1;
						timeAnimation = 0;
					}
				}
				else
				{
					m_inversePositionY = -1;
					m_PositionBody.y = 18;
					timeAnimation = 0;
					m_Body = m_Run;
					m_Body->getAnimation()->UpdateAnimationInverse(250); 
				}
			}
		}
	}
	else
	{
		m_Body = m_Shoot;
		if(CInputDx9::getInstance()->IsKeyDown(DIK_Z))
		{
			this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(this->timeAnimation > 100)
			{
				m_PositionBody.y += 2 * m_inversePositionY;
				m_inversePositionY *= -1;
				timeAnimation = 0;
			}
		}
		else
		{
			m_inversePositionY = -1;
			m_PositionBody.y = 18;
			timeAnimation = 0;
			m_Body->getAnimation()->UpdateAnimationInverse(250); 
		}
		m_Body->getAnimation()->Reset();
		m_Leg->getAnimation()->Reset();
	}
	//code nay de lam cai hieu ung giat giat khi ban dan
	//this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	//if(this->timeAnimation > 100)
	//{
	//	m_PositionBody.y += 2 * m_inversePositionY;
	//	m_inversePositionY *= -1;
	//	timeAnimation = 0;
	//}
}

void RamboSprite::Reset()
{
	m_Body->getAnimation()->Reset();
	m_Leg->getAnimation()->Reset();
}

void RamboSprite::Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep)
{
	m_Leg->Render(spriteHandle, D3DXVECTOR2(position.x, position.y + m_PositionLeg.y), effect, rotateAngle, scale, deep);
	m_Body->Render(spriteHandle, D3DXVECTOR2(position.x, position.y + m_PositionBody.y), effect, rotateAngle, scale, deep);
}

RamboSprite::~RamboSprite(void)
{
}
