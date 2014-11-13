#include "LedObject.h"


LedObject* LedObject::s_Instance = 0;

LedObject::LedObject()
{

}

LedObject* LedObject::getStaticInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new LedObject();
	}
	return s_Instance;
}

LedObject::LedObject(D3DXVECTOR3 _position, eObjectID _objectID)
{
	this->m_Position = _position;
	this->m_eObjectID = _objectID;
}

void LedObject::Initialize()
{
	this->m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	this->m_Sprite = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_LED_OBJECT);
}

void LedObject::UpdateAnimation()
{
	this->getSprite()->UpdateAnimation(300);
}

void LedObject::UpdateCollision(Object* _checkingObject)
{

}

void LedObject::Update()
{

}

void LedObject::Render(SPRITEHANDLE _spriteHandler)
{
	if(this->m_Sprite != NULL)
	{
		this->m_Sprite->Render(_spriteHandler, D3DXVECTOR2(this->m_Position.x, this->m_Position.y), this->getSprite()->getSpriteEffect(), this->getSprite()->getRotate(), 
			this->getSprite()->getScale(), this->m_Position.z);
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
