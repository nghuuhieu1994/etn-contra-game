#include "Tinker.h"

Tinker::Tinker(){}

Tinker::Tinker(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
: DynamicObject(_position, _direction, _objectID)
{
}

void Tinker::Initialize()
{
	timeDelayGun = 0;
	this->m_ObjectState = eObjectState::STATE_ALIVE_IDLE;
	this->isDead = false;
	this->m_BossBodyAlive = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_BODY_ALIVE);
	this->m_BossBodyDead = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_BODY_DEAD);
	this->m_Explosion = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_EXPLOISION);
	this->m_BossDie = SpriteManager::getInstance()->getSprite(eSpriteID::SPRITE_BOSS_DIE);
	
	m_Center = new BossCenter(D3DXVECTOR3(this->getPositionVec3().x - 80, this->getPositionVec3().y - 80, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_CENTER);
	m_Center->Initialize();
	m_Left = new BossGun(D3DXVECTOR3(this->getPositionVec3().x - 90, this->getPositionVec3().y + 13, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Left->Initialize();
	m_Right = new BossGun(D3DXVECTOR3(this->getPositionVec3().x - 30, this->getPositionVec3().y + 13, this->getPositionVec3().z), eDirection::LEFT, eObjectID::BOSS_GUN);
	m_Right->Initialize();
	m_Sprite = m_BossBodyAlive;
	m_Left->getSprite()->getAnimationAction()->setCurrentFrame(0);
	m_Right->getSprite()->getAnimationAction()->setCurrentFrame(1);
}

void Tinker::UpdateAnimation()
{
	switch (m_ObjectState)
	{
	case STATE_ALIVE_IDLE:
		timeDelayGun += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
		if (timeDelayGun > 1000)
		{
			if (m_Left->getSprite()->getAnimationAction()->getCurrentIndex() == 0)
			{
				m_Left->getSprite()->getAnimationAction()->setCurrentFrame(1);
			}
			else
			{
				m_Left->getSprite()->getAnimationAction()->setCurrentFrame(0);
			}

			if (m_Right->getSprite()->getAnimationAction()->getCurrentIndex() == 0)
			{
				m_Right->getSprite()->getAnimationAction()->setCurrentFrame(1);
			}
			else
			{
				m_Right->getSprite()->getAnimationAction()->setCurrentFrame(0);
			}
			timeDelayGun = 0;
		}
		m_Center->UpdateAnimation();
		break;
	case STATE_BEFORE_DEATH:
		if (isDead != true)
		{
			SoundManagerDx9::getInstance()->getSoundBuffer(eSoundID::boss_dead_sfx)->Play();
			isDead = true;
		}
		m_BossDie->UpdateAnimation(750);
		m_Explosion->UpdateAnimation(150);
		break;
	case STATE_BOSS_DEATH:
		m_Sprite = m_BossBodyDead;
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
		if (m_Center->getObjectState() == eObjectState::STATE_DEATH)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 500)
			{
				m_TimeChangeState = 0;
				this->m_ObjectState = eObjectState::STATE_BEFORE_DEATH;
			}
		}
		break;

	case STATE_BEFORE_DEATH:
		if (isDead)
		{
			m_TimeChangeState += CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();
			if (m_TimeChangeState > 6000)
			{
				m_TimeChangeState = 0;
				this->m_ObjectState = eObjectState::STATE_BOSS_DEATH;
			}
		}
		break;
	case STATE_BOSS_DEATH:
		Release();
		break;
	default:
		break;
	}
}

void Tinker::Render(SPRITEHANDLE spriteHandle)
{
	if (m_Left)
	{
		m_Left->Render(spriteHandle);
	}
	if (m_Right)
	{
		m_Right->Render(spriteHandle);
	}

	if (m_Sprite != NULL)
	{
		m_Sprite->Render(spriteHandle,
					getPositionVec2(),
					m_Sprite->getSpriteEffect(),
					m_Sprite->getRotate(),
					m_Sprite->getScale(),
					m_Position.z);
	}

	if (m_Center)
	{
		m_Center->Render(spriteHandle);
	}

	if (isDead && m_Explosion && m_BossDie)
	{
		m_BossDie->Render(spriteHandle, D3DXVECTOR2(m_Position.x - 14, m_Position.y - 75), ESpriteEffect::None, 0.0f, 1.0f, m_Position.z);
		m_Explosion->Render(spriteHandle, D3DXVECTOR2(m_Position.x + 5, m_Position.y - 90), ESpriteEffect::None, 0.0f, 1.0f, m_Position.z);
	}
}

void Tinker::Release()
{
	//m_Right->Release();
	SAFE_DELETE(m_Right);
	//m_Left->Release();
	SAFE_DELETE(m_Left);
	//m_Center->Release();
	SAFE_DELETE(m_Center);

	m_BossDie = 0;
	m_Explosion = 0;
}

Tinker::~Tinker()
{}