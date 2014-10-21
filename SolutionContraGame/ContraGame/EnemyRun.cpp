#include "EnemyRun.h"

EnemyRun::EnemyRun()
{}

EnemyRun::EnemyRun(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position = _position;
}

void EnemyRun::Initialize()
{
	m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	sprite_dead = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	sprite_main = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_ENEMY_RUN));
	m_Sprite = sprite_main;
}

void EnemyRun::UpdateAnimation()
{
	m_Sprite->UpdateAnimation(300);
}
void EnemyRun::UpdateCollision(Object* checkingObject)
{

}
void EnemyRun::UpdateMovement()
{
}
void EnemyRun::Update()
{
}

void EnemyRun::Render(SPRITEHANDLE spriteHandle)
{
	if(m_Sprite != 0)
	{
		m_Sprite->Render(spriteHandle, getPositionVec2(), m_Sprite->getSpriteEffect(), m_Sprite->getRotate(), m_Sprite->getScale(), m_Position.z);
	}
}

void EnemyRun::Release()
{
	m_Sprite = 0;
	sprite_dead->Release();
	sprite_main->Release();
}
EnemyRun::~EnemyRun()
{
}