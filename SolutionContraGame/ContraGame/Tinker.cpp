#include "Tinker.h"

Tinker::Tinker(){}

Tinker::Tinker(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{
}

void Tinker::Initialize()
{
	this->m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	this->m_BodyAlive = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_BODY);	
	m_Sprite = m_BodyAlive;

	m_BodyDeath = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_DEATH);
	m_Center = new BossCenter(D3DXVECTOR3(this->getPositionVec3().x - 80, this->getPositionVec3().y - 80, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_CENTER);
	m_Center->Initialize();
	m_Left = new BossGun(D3DXVECTOR3(this->getPositionVec3().x - 50, this->getPositionVec3().y - 50, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Left->Initialize();
	m_Right = new BossGun(D3DXVECTOR3(this->getPositionVec3().x + 50, this->getPositionVec3().y + 50, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Right->Initialize();

	isBurned = false;
}

void Tinker::UpdateAnimation()
{
	m_Left->UpdateAnimation();
	m_Right->UpdateAnimation();
	m_Center->UpdateAnimation();
}

void Tinker::UpdateCollision(Object* checkingObject)
{
	if(m_Left->getObjectState() != eObjectState::STATE_DEATH)
	{
		m_Left->UpdateCollision(checkingObject);
	}
	if(m_Right->getObjectState()  != eObjectState::STATE_DEATH)
	{
		m_Right->UpdateCollision(checkingObject);
	}
	if(m_Center->getObjectState() != eObjectState::STATE_DEATH)
	{
		m_Center->UpdateCollision(checkingObject);
	}
}

void Tinker::UpdateMovement(){}

void Tinker::Update()
{
	if(m_Center->getObjectState() != eObjectState::STATE_DEATH)
	{
		m_Center->Update();
	}
	if(m_Left->getObjectState() != eObjectState::STATE_DEATH)
	{
		m_Left->Update();
	}
	if(m_Right->getObjectState() != eObjectState::STATE_DEATH)
	{
		m_Right->Update();
	}

	switch (this->m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		if(m_Left->getObjectState() == eObjectState::STATE_DEATH &&
			m_Right->getObjectState() == eObjectState::STATE_DEATH &&
			m_Center->getObjectState() == eObjectState::STATE_DEATH)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 696)
			{
				this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
			}
		}
		break;
	case STATE_BEFORE_DEATH:
		if(isBurned == true)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 3500)
			{
				this->m_ObjectState = eObjectState::STATE_DEATH;
			}
		}
		else
		{
			// createBurningFunc
		}
		break;
	case STATE_DEATH:
		this->Release();
		break;
	default:
		break;
	}
}

void Tinker::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Sprite != NULL)
	{
		m_Sprite->Render(spriteHandle,
			getPositionVec2(),
			m_Sprite->getSpriteEffect(),
			m_Sprite->getRotate(),
			m_Sprite->getScale(),
			m_Position.z);
	}
	m_Left->Render(spriteHandle);
	m_Right->Render(spriteHandle);
	m_Center->Render(spriteHandle);
}

void Tinker::Release()
{
	m_Center = NULL;
	m_Sprite = NULL;
}

Tinker::~Tinker()
{}