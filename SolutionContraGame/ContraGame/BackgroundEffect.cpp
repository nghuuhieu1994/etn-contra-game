#include "BackgroundEffect.h"
#include "CCamera.h"

BackgroundEffect::BackgroundEffect()
{
	
}

void BackgroundEffect::Initialize(int _tile_effect)
{
	timeStar = 0;
	delayStar = 0;
	if (_tile_effect == eSpriteID::SPRITE_MAP_1)
	{
		this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EFFECT_MAP1)); 
	}
	if (_tile_effect == eSpriteID::SPRITE_MAP_2)
	{
		this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EFFECT_MAP2)); 
	}
	if (_tile_effect == eSpriteID::SPRITE_MAP_3)
	{
		this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EFFECT_MAP3)); 
	}
}

void BackgroundEffect::UpdateAnimation()
{
	m_Sprite->UpdateAnimation(350);
}


void BackgroundEffect::Render(SPRITEHANDLE _spriteHandler)
{	

	RECT sourceRect;
	sourceRect.top = (long)(m_Sprite->getAnimation()->getFrameSize().y - Camera::getInstance()->getBound().top + m_Sprite->getAnimation()->getCurrentIndex() % m_Sprite->getAnimation()->getRowFrame() * m_Sprite->getAnimation()->getFrameSize().y);
	sourceRect.bottom = (long)(m_Sprite->getAnimation()->getFrameSize().y - Camera::getInstance()->getBound().bottom + m_Sprite->getAnimation()->getCurrentIndex() % m_Sprite->getAnimation()->getRowFrame() * m_Sprite->getAnimation()->getFrameSize().y);
	sourceRect.right = (long)(Camera::getInstance()->getBound().right + m_Sprite->getAnimation()->getCurrentIndex() % m_Sprite->getAnimation()->getColumnFrame() * m_Sprite->getAnimation()->getFrameSize().x);
	sourceRect.left = (long)(Camera::getInstance()->getBound().left + m_Sprite->getAnimation()->getCurrentIndex() % m_Sprite->getAnimation()->getColumnFrame() * m_Sprite->getAnimation()->getFrameSize().x);

	m_Sprite->getMyTexture()->RenderWithoutTransform(_spriteHandler, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(1.0f, -1.0f), 0.0f, 0xffffffff, &sourceRect, 0.9f);
	//m_Sprite->Render(_spriteHandler, D3DXVECTOR2(m_Sprite->getMyTexture()->m_Width/2, m_Sprite->getMyTexture()->m_Height /2), ESpriteEffect::None, 0.0f, 1.0f, 0.9f);
}

void BackgroundEffect::Release()
{
	this->m_Sprite->Release();
	this->m_Sprite = 0;
}

BackgroundEffect::~BackgroundEffect()
{

}
