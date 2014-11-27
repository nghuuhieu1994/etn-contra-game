#include "LedObject.h"
#include "CCamera.h"

LedObject::LedObject()
{
	timeStar = 0;
	delayStar = 0;
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EFFECT_MAP1));
}


LedObject::LedObject(D3DXVECTOR3 _position, eObjectID _objectID) : Object(_position, eDirection::NONE, _objectID)
{
	timeStar = 0;
	delayStar = 0;
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EFFECT_MAP1));
}

void LedObject::Initialize()
{
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EFFECT_MAP1));
}

void LedObject::UpdateAnimation()
{
	
}

void LedObject::UpdateCollision(Object* _checkingObject)
{

}

void LedObject::Update()
{

}

void LedObject::Render(SPRITEHANDLE _spriteHandler)
{	
	m_Sprite->UpdateAnimation(200);
	RECT sourceRect;
	sourceRect.top = Camera::getInstance()->getBound().top + m_Sprite->getAnimation()->getCurrentIndex() * m_Sprite->getAnimation()->getFrameSize().y;
	sourceRect.bottom = Camera::getInstance()->getBound().bottom + m_Sprite->getAnimation()->getCurrentIndex() * m_Sprite->getAnimation()->getFrameSize().y;
	sourceRect.right = Camera::getInstance()->getBound().right;
	sourceRect.left = Camera::getInstance()->getBound().left;

	m_Sprite->getMyTexture()->RenderWithoutTransform(_spriteHandler, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(1.0f, -1.0f), 0.0f, 0xffffffff, &sourceRect, 0.9f);
}

void LedObject::Release()
{
	this->m_Sprite->Release();
	this->m_Sprite = NULL;
}

LedObject::~LedObject()
{

}
