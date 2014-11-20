#include "Explosion.h"

Explosion::Explosion()
{

}

Explosion::Explosion(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	
	
	
}

void Explosion::Initialize()
{
	m_Sprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BRIDGE_EXPLOSION));
}

void Explosion::UpdateAnimation()
{
	m_Sprite->getAnimationAction()->setIndexStart(0);
	m_Sprite->getAnimationAction()->setIndexEnd(2);
}


void Explosion::UpdateCollision(Object* checkingObject)
{

}



void Explosion:: UpdateMovement()
{

}

void Explosion::Update()
{

}

void Explosion::Render(SPRITEHANDLE spriteHandle)
{
	m_Sprite->Render(spriteHandle, getPositionVec2() , m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
}

void Explosion::Release()
{

}

Explosion::~Explosion()
{

}