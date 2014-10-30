#include "RamboMoveSprite.h"


RamboMoveSprite::RamboMoveSprite(void)
{
	m_Body = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_MOVE_BODY));
	m_Leg = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_RAMBO_MOVE_LEG));
	m_PositionBody = D3DXVECTOR3(0, 28, 0);
	m_PositionLeg = D3DXVECTOR3(0, 0, 0);
	//m_inversePositionY = -1;
	//timeAnimation = 0;
}

void RamboMoveSprite::UpdateAnimation()
{
	m_Body->getAnimation()->UpdateAnimationInverse(250);
	m_Leg->getAnimation()->UpdateAnimation(250);

	//code nay de lam cai hieu ung giat giat khi ban dan
	//this->timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	//if(this->timeAnimation > 100)
	//{
	//	m_PositionBody.y += 2 * m_inversePositionY;
	//	m_inversePositionY *= -1;
	//	timeAnimation = 0;
	//}
}

void RamboMoveSprite::Reset()
{
	m_Body->getAnimation()->Reset();
	m_Leg->getAnimation()->Reset();
}

void RamboMoveSprite::Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep)
{
	m_Body->Render(spriteHandle, D3DXVECTOR2(position.x, position.y + m_PositionBody.y), effect, rotateAngle, scale, deep);
	m_Leg->Render(spriteHandle, D3DXVECTOR2(position.x, position.y + m_PositionLeg.y), effect, rotateAngle, scale, deep);
}

RamboMoveSprite::~RamboMoveSprite(void)
{
}
