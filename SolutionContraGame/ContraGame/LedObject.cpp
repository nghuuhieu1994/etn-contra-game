#include "LedObject.h"

LedObject::LedObject()
{
	timeStar = 0;
	delayStar = 0;
}


LedObject::LedObject(D3DXVECTOR3 _position, eObjectID _objectID) : Object(_position, eDirection::NONE, _objectID)
{
	
	/*this->m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	this->m_Sprite = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_LED_OBJECT);*/
	timeStar = 0;
	delayStar = 0;
}

void LedObject::Initialize()
{

	//this->m_Sprite = this->m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_LED_OBJECT));
}

void LedObject::UpdateAnimation()
{
	/*this->getSprite()->UpdateAnimation(400);*/
}

void LedObject::UpdateCollision(Object* _checkingObject)
{

}

void LedObject::Update()
{

}

void LedObject::Render(SPRITEHANDLE _spriteHandler)
{
	/*if(this->m_Sprite != NULL)
	{
		this->m_Sprite->Render(_spriteHandler, D3DXVECTOR2(this->m_Position.x, this->m_Position.y), this->getSprite()->getSpriteEffect(), this->getSprite()->getRotate(), 
			this->getSprite()->getScale(), this->m_Position.z);
	}*/
	timeStar += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
	if (timeStar > 200)
	{
		delayStar += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_TRICK)->Render(_spriteHandler, D3DXVECTOR2(3264, 224), ESpriteEffect::None, 0.0f, 1.0f, 1.0f);
		if (delayStar > 200)
		{
			delayStar = 0;
			timeStar = 0;
		}
	}
}

void LedObject::Release()
{
	/*this->m_Sprite->Release();
	this->m_Sprite = NULL;*/
}

LedObject::~LedObject()
{

}
