#include "Tinker.h"

Tinker::Tinker(){}

Tinker::Tinker(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{
}

void Tinker::Initialize()
{
	timeDelayGun = 0;
	isDelay = false;
	this->m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	this->m_BossBodyAlive = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_BODY_ALIVE);
	this->m_BossBodyDead = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_BODY_DEAD);
	m_Center = new BossCenter(D3DXVECTOR3(this->getPositionVec3().x - 80, this->getPositionVec3().y - 80, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_CENTER);
	m_Center->Initialize();
	m_Left = new BossGun(D3DXVECTOR3(this->getPositionVec3().x - 85, this->getPositionVec3().y + 13, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Left->Initialize();
	m_Right = new BossGun(D3DXVECTOR3(this->getPositionVec3().x - 30, this->getPositionVec3().y + 13, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Right->Initialize();
	m_Sprite = m_BossBodyAlive;
}

void Tinker::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		if(isDelay == false)
		{
			timeDelayGun += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		}
		if(timeDelayGun > 1000)
		{
			isDelay = true;
			timeDelayGun = 0;
		}
		if(isDelay)
		{
			m_Left->UpdateAnimation();
		}
		m_Right->UpdateAnimation();
		m_Center->UpdateAnimation();
		break;
	case STATE_BEFORE_DEATH:
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}

}

void Tinker::UpdateCollision(Object* checkingObject)
{
	m_Left->UpdateCollision(checkingObject);
	m_Right->UpdateCollision(checkingObject);
	m_Center->UpdateCollision(checkingObject);
}

void Tinker::UpdateMovement(){}

void Tinker::Update()
{
	switch (this->m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		m_Center->Update();
		m_Left->Update();
		m_Right->Update();

		if(m_Center->getObjectState() == eObjectState::STATE_DEATH)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 500)
			{
				m_TimeChangeState = 0;
				this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
				//Burn!!!!! Sound
			}
		}
		break;
	case STATE_BEFORE_DEATH:
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 3000)
			{
				m_TimeChangeState = 0;
				this->m_ObjectState = eObjectState::STATE_DEATH;
				//Burn!!!!! Sound
			}
		break;
	case STATE_DEATH:
		break;
	default:
		break;
	}
}

void Tinker::Render(SPRITEHANDLE spriteHandle)
{
	m_Left->Render(spriteHandle);
	m_Right->Render(spriteHandle);
	if (m_Sprite != NULL)
	{
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			m_Sprite->getSpriteEffect(),
			m_Sprite->getRotate(),
			m_Sprite->getScale(),
			m_Position.z);
	}
	m_Center->Render(spriteHandle);
}

void Tinker::Release()
{
	SAFE_DELETE(m_Right);
	SAFE_DELETE(m_Left);
	SAFE_DELETE(m_Center);
}

Tinker::~Tinker()
{}