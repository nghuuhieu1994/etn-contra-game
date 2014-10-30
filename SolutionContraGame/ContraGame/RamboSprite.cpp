#include "RamboSprite.h"


RamboSprite::RamboSprite(void)
{
	this->m_Body	= 0;
	this->m_Leg		= 0;
}

D3DXVECTOR2 RamboSprite::GetFrameSize()
{
	/*
	tempBound.left = m_Position.x - m_Sprite->getAnimation()->getFrameSize().x / 2;
	tempBound.right = tempBound.left + m_Sprite->getAnimation()->getFrameSize().x;
	tempBound.top = m_Position.y + m_Sprite->getAnimation()->getFrameSize().y / 2;
	tempBound.bottom = tempBound.top - m_Sprite->getAnimation()->getFrameSize().y;*/
	D3DXVECTOR2 result;
	if (m_Leg != 0)
	{
		result.x = max(m_Body->getAnimation()->getFrameSize().x, m_Leg->getAnimation()->getFrameSize().x);
		result.y = m_Body->getAnimation()->getFrameSize().y + m_Leg->getAnimation()->getFrameSize().y;
		return result;
	}
	else
	{ 
		return m_Body->getAnimation()->getFrameSize();
	}
}

RamboSprite::~RamboSprite(void)
{
}
