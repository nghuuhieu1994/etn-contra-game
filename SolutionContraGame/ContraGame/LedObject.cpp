#include "LedObject.h"
#include "CCamera.h"

LedObject::LedObject()
{
	timeStar = 0;
	delayStar = 0;
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EFFECT_MAP1_0));
}


LedObject::LedObject(D3DXVECTOR3 _position, eObjectID _objectID) : Object(_position, eDirection::NONE, _objectID)
{
	timeStar = 0;
	delayStar = 0;
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EFFECT_MAP1_0));
}

void LedObject::Initialize()
{
	this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EFFECT_MAP1_0));
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
	
	
	timeStar += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (timeStar > 200)
	{
		delayStar += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		m_Sprite->getMyTexture()->RenderWithoutTransform(_spriteHandler, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(1.0f, -1.0f), 0.0f, 0xffffffff, &Camera::getInstance()->getBound(), 0.9f);
		if (delayStar > 200)
		{
			delayStar = 0;
			timeStar = 0;
		}
	}
}

void LedObject::Release()
{
	this->m_Sprite->Release();
	this->m_Sprite = NULL;
}

LedObject::~LedObject()
{

}
