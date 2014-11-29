#include "TankTile.h"

TankTile::TankTile(){}

TankTile::TankTile(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{

}
TankTile::~TankTile(){}

void TankTile::Initialize()
{
	m_TankSprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_TANK));
	m_DeadSprite = new CSpriteDx9(*SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_EXPLOISION));
	m_Sprite = m_TankSprite; 
	m_ObjectState = STATE_ALIVE_IDLE;
	m_AttackCounter = 12;
}

void TankTile::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		this->m_Sprite->getAnimationAction()->setIndexStart(0);
		this->m_Sprite->getAnimationAction()->setIndexEnd(23);
		m_Sprite->UpdateAnimation(500);
		break;
	case STATE_BEFORE_DEATH:
		if (isDead != true)
		{
			m_Sprite = m_DeadSprite;
			isDead = true;
		}
		m_Sprite->UpdateAnimation(250);
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}
void TankTile::UpdateCollision(Object* checkingObject)
{

}
void TankTile::Update()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		break;
	case STATE_BEFORE_DEATH:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeState > 1000)
		{
			m_ObjectState = eObjectState::STATE_DEATH;
			m_TimeChangeState = 0;
		}
		break;
	case STATE_DEATH:
		m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (m_TimeChangeState > 300)
		{
			this->Release();
			m_TimeChangeState = 0;
		}
		break;
	}
}
void TankTile::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite)
	{
		if (m_Sprite != m_DeadSprite)
		{
			m_Sprite->Render(spriteHandle,
				getPositionVec2(),
				m_Sprite->getSpriteEffect(),
				m_Sprite->getRotate(),
				m_Sprite->getScale(),
				m_Position.z);
		}
		else
		{
			m_Sprite->Render(spriteHandle,
				D3DXVECTOR2(m_Position.x - 30, m_Position.y - 10),
				m_Sprite->getSpriteEffect(),
				m_Sprite->getRotate(),
				m_Sprite->getScale(),
				m_Position.z);
			m_Sprite->Render(spriteHandle,
				D3DXVECTOR2(m_Position.x + 30, m_Position.y + 10),
				m_Sprite->getSpriteEffect(),
				m_Sprite->getRotate(),
				m_Sprite->getScale(),
				m_Position.z);
			m_Sprite->Render(spriteHandle,
				D3DXVECTOR2(m_Position.x - 10, m_Position.y - 20),
				m_Sprite->getSpriteEffect(),
				m_Sprite->getRotate(),
				m_Sprite->getScale(),
				m_Position.z);
			m_Sprite->Render(spriteHandle,
				D3DXVECTOR2(m_Position.x - 10, m_Position.y + 20),
				m_Sprite->getSpriteEffect(),
				m_Sprite->getRotate(),
				m_Sprite->getScale(),
				m_Position.z);
		}
	}
}
void TankTile::Release()
{
	m_TankSprite->Release();
	m_DeadSprite->Release();
	m_Sprite = 0;
}
