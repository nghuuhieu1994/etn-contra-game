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

	this->m_BossBody = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_BODY);
	m_Sprite = m_BossBody;

	m_Center = new BossCenter(D3DXVECTOR3(this->getPositionVec3().x - 80, this->getPositionVec3().y - 80, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_CENTER);
	m_Center->Initialize();
	m_Left = new BossGun(D3DXVECTOR3(this->getPositionVec3().x - 85, this->getPositionVec3().y + 13, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Left->Initialize();
	m_Right = new BossGun(D3DXVECTOR3(this->getPositionVec3().x - 30, this->getPositionVec3().y + 13, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Right->Initialize();
}

void Tinker::UpdateAnimation()
{
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
		if(m_Center->getObjectState() == eObjectState::STATE_DEATH)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if(m_TimeChangeState > 1000)
			{
				m_TimeChangeState = 0;
				this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
			}
		}
		break;
	case STATE_BEFORE_DEATH:
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
	m_Center = NULL;
	m_Sprite = NULL;
	m_Left = NULL;
	m_Right = NULL;
}

Tinker::~Tinker()
{}